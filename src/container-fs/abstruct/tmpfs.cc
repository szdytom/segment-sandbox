#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::AbstructContainerFS::_mountTmp() {
    if (mkdir("/tmp", S_IRWXU | S_IRWXG | S_IRWXO))
        throw ssandbox::utils::exceptions::syscall_error(errno, "Cannot make directory for /tmp", __FUNCTION__);

    if (mount("tmpfs", "/tmp", "tmpfs", 0, nullptr))
        throw ssandbox::utils::exceptions::syscall_error(errno, "Cannot mount fs of tmpfs", __FUNCTION__);
}

void ssandbox::AbstructContainerFS::_umountTmp() {
    std::string tmppath((this->getFSPath("target") / "tmp").native());
    if (umount2(tmppath.c_str(), MNT_FORCE))
        throw ssandbox::utils::exceptions::syscall_error(errno, "Cannot umount fs of tmpfs", __FUNCTION__);

    if (rmdir(tmppath.c_str()))
        throw ssandbox::utils::exceptions::syscall_error(errno, "Cannot remove directory /tmp", __FUNCTION__);
}