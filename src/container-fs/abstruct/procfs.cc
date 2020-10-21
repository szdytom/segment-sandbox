#include <fmt/core.h>
#include <sys/mount.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::abstruct_container_fs::_mount_proc() {
    if (mount("proc", "/proc", "proc", 0, nullptr))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot mount fs of proc", __FUNCTION__);
}
