#include <fmt/format.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::OverlayContainerFS::mountMain() {
    std::string options(fmt::format("lowerdir={},upperdir={},workdir={}", this->image_path.native(), this->getFSPath("target").native(), this->getFSPath("overlayfs_work").native()));

    if (mount("overlay", this->getFSPath("/").c_str(), "overlay", 0, options.c_str()))
        throw ssandbox::utils::exceptions::syscall_error(errno, "Cannot mount overlayfs", __FUNCTION__);
}