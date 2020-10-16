#include <cerrno>
#include <fmt/core.h>
#include <sys/mount.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::readonly_container_fs::umount_main() {
    int res = umount2(this->get_fs_path("target").c_str(), MNT_FORCE);
    if (res)
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot umount readonly bind of {} with return code {}", this->image_path.string(), res), __FUNCTION__);
}