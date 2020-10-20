#include <cerrno>
#include <fmt/core.h>
#include <sys/mount.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::readonly_container_fs::mount_main() {
    if (mount(this->image_path.c_str(), this->get_fs_path("target").c_str(), "", MS_BIND | MS_REC, ""))
        throw ssandbox::exceptions::syscall_error(
            errno, fmt::format("Cannot bind mainfs from '{}'", this->image_path.string()), __FUNCTION__);

    if (mount("", this->get_fs_path("target").c_str(), "", MS_BIND | MS_REMOUNT | MS_RDONLY | MS_NOATIME | MS_REC, ""))
        throw ssandbox::exceptions::syscall_error(
            errno, fmt::format("Cannot remount mainfs", this->image_path.string()), __FUNCTION__);
}