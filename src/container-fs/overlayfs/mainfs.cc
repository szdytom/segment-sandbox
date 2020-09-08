#include <fmt/format.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::OverlayContainerFS::mountMain() {
    std::string options(fmt::format("lowerdir={},upperdir={},workdir={}", this->image_path.native(), this->getFSPath("overlay_upper").native(), this->getFSPath("overlayfs_work").native()));

    if (mount("overlay", this->getFSPath("target").c_str(), "overlay", 0, options.c_str()))
        throw ssandbox::utils::exceptions::syscall_error(errno, "Cannot mount overlayfs", __FUNCTION__);
}

void ssandbox::OverlayContainerFS::umountMain() {
    if (umount2(this->getFSPath("target").c_str(), MNT_FORCE))
        throw ssandbox::utils::exceptions::syscall_error(errno, "Cannot umount fs of overlayfs", __FUNCTION__);
}