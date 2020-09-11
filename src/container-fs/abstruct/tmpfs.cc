#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::AbstructContainerFS::_mount_tmp() {
    if (mkdir("/tmp", S_IRWXU | S_IRWXG | S_IRWXO))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot make directory for /tmp", __FUNCTION__);

    if (mount("tmpfs", "/tmp", "tmpfs", 0, nullptr))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot mount fs of tmpfs", __FUNCTION__);
}

void ssandbox::AbstructContainerFS::_umount_tmp() {
    std::string tmppath((this->get_fs_path("target") / "tmp").string());
    if (umount2(tmppath.c_str(), MNT_FORCE))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot umount fs of tmpfs", __FUNCTION__);

    if (rmdir(tmppath.c_str()))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot remove directory /tmp", __FUNCTION__);
}