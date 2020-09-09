// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef CONTAINERFS_H
#define CONTAINERFS_H

#include <filesystem>
#include <memory>
#include <sys/mount.h>

namespace ssandbox {

struct MountInfo {
    /* will be mount to here in you host machine */
    std::filesystem::path point;
    /* Mount source in your host machine (Lower Directory) */
    std::filesystem::path lower_dir;
    /* Temp Working Dir for overlay */
    std::filesystem::path workspace;
    /* Upper Directory */
    std::filesystem::path upper_dir;

    /* An extra point to mount, will be mounted into /mnt inside container*/
    std::filesystem::path extra_point;

    /* If enabled, it will mount /proc */
    bool mount_proc;

    /* If enabled, it will mount /tmp */
    bool mount_tmp;
};

class AbstructContainerFS {
public:
    void mountAll();
    void umountAll();

    void enableTmp(bool enable = true);
    void enableProc(bool enable = true);
    void setUID(const std::string& uid);
    void setWorkspace(const std::filesystem::path& workspace_path);
    void setImage(const std::filesystem::path& image_path);

protected:
    std::filesystem::path getFSPath(const std::filesystem::path& name);

    virtual void mountMain() {};
    virtual void umountMain() {};

    virtual void mountExtra() {};
    virtual void umountExtra() {};

    std::string uid;
    std::filesystem::path workspace;
    std::filesystem::path image_path;

private:
    void _mountTmp();
    void _mountProc();

    void _umountTmp();
    void _umountProc();

    void _changeRoot();

    bool _mount_tmp;
    bool _mount_proc;
};

class OverlayContainerFS : public AbstructContainerFS {
protected:
    void mountMain();
    void umountMain();
};

void mount_containerfs(MountInfo cfg);
void umount_containerfs(MountInfo cfg);

} /* namespace ssandbox */

#endif /* CONTAINERFS_H */