#include <fmt/core.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::OverlayContainerFS::mount_main() {
    std::string options(fmt::format("lowerdir={},upperdir={},workdir={}", this->image_path.string(), this->get_fs_path("overlay_upper").string(), this->get_fs_path("overlayfs_work").string()));

    if (mount("overlay", this->get_fs_path("target").c_str(), "overlay", 0, options.c_str()))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot mount overlayfs", __FUNCTION__);
}

void ssandbox::OverlayContainerFS::umount_main() {
    if (umount2(this->get_fs_path("target").c_str(), MNT_FORCE))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot umount fs of overlayfs", __FUNCTION__);
}