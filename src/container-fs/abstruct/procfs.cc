#include <fmt/core.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::abstruct_container_fs::_mount_proc() {
    if (mount("proc", "/proc", "proc", 0, nullptr))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot mount fs of proc", __FUNCTION__);
}

void ssandbox::abstruct_container_fs::_umount_proc() {
    std::string proc_path((this->get_fs_path("target") / "proc").string());
    if (umount2(proc_path.c_str(), MNT_FORCE))
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot umount fs of procfs at '{}'", proc_path),
                                                  __FUNCTION__);
}