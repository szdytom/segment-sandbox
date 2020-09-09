// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef CONTAINERFS_H
#define CONTAINERFS_H

#include <filesystem>
#include <memory>
#include <sys/mount.h>

namespace ssandbox {

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

} /* namespace ssandbox */

#endif /* CONTAINERFS_H */