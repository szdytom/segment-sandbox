#include "ssandbox/containerfs.h"

ssandbox::AbstructContainerFS::AbstructContainerFS() {
    this->_mount_proc_flag = true;
    this->_mount_tmp_flag = true;
}

ssandbox::AbstructContainerFS::~AbstructContainerFS() {}