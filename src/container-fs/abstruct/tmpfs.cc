#include <fmt/core.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::abstruct_container_fs::_mount_tmp() {
    if (mount("tmpfs", "/tmp", "tmpfs", 0, nullptr))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot mount fs of tmpfs", __FUNCTION__);
}
