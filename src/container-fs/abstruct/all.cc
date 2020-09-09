#include <fmt/core.h>
#include <unistd.h>
#include "ssandbox/containerfs.h"
#include "ssandbox/utils/exceptions.h"

void ssandbox::AbstructContainerFS::mountAll() {
    this->mountMain();
    this->_changeRoot();

    if (this->_mount_tmp)
        this->_mountTmp();

    if (this->_mount_proc)
        this->_mountProc();

    this->mountExtra();
}

void ssandbox::AbstructContainerFS::umountAll() {
    if (this->_mount_tmp)
        this->_umountTmp();

    if (this->_mount_proc)
        this->_umountProc();

    this->umountMain();
    this->umountExtra();
}

void ssandbox::AbstructContainerFS::_changeRoot() {
    if (chdir(this->getFSPath("target").c_str()))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot change working point", __FUNCTION__);

    if (chroot("./"))
        throw ssandbox::exceptions::syscall_error(errno, "Cannot change root mount point", __FUNCTION__);
}