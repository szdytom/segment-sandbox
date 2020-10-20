// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef CONTAINERFS_H
#define CONTAINERFS_H

#include <filesystem>
#include <memory>
#include <sys/mount.h>

namespace ssandbox {

class abstruct_container_fs {
public:
    void mount_all();

    void enable_tmp(bool enable = true);
    void enable_proc(bool enable = true);
    void set_uid(const std::string& uid);
    void set_workspace(const std::filesystem::path& workspace_path);
    void set_image(const std::filesystem::path& image_path);

protected:
    std::filesystem::path get_fs_path(const std::filesystem::path& name) const;

    virtual void mount_main(){};
    virtual void mount_extra(){};

    std::string uid;
    std::filesystem::path workspace;
    std::filesystem::path image_path;

    abstruct_container_fs();
    ~abstruct_container_fs();

private:

    void _mount_tmp();
    void _mount_proc();

    void _change_root();

    bool _mount_tmp_flag;
    bool _mount_proc_flag;
};

class OverlayContainerFS : public abstruct_container_fs {
protected:
    void mount_main() override final;
};

class readonly_container_fs : public abstruct_container_fs {
protected:
    void mount_main() override final;
};

} /* namespace ssandbox */

#endif /* CONTAINERFS_H */