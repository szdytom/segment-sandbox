#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::AbstructContainerFS::_mount_proc() {
    if (mkdir("/proc", S_IRWXU | S_IRWXG | S_IRWXO))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot make directory for /proc", __FUNCTION__);

    if (mount("proc", "/proc", "proc", 0, nullptr))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot mount fs of proc", __FUNCTION__);
}

void ssandbox::AbstructContainerFS::_umount_proc() {
    std::string proc_path((this->get_fs_path("target") / "proc").string());
    if (umount2(proc_path.c_str(), MNT_FORCE))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot umount fs of proc", __FUNCTION__);

    if (rmdir(proc_path.c_str()))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot remove directory /proc", __FUNCTION__);
}