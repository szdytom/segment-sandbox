#include <cerrno>
#include <fmt/core.h>
#include <sys/mount.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::readonly_container_fs::mount_main() {
    int res = mount(this->image_path.c_str(), this->get_fs_path("target").c_str(), nullptr, MS_BIND | MS_RDONLY, nullptr);
    if (res)
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot mount readonly bind of {} with return code {}", this->image_path.string(), res), __FUNCTION__);
}