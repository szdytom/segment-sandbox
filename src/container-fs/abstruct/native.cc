#include "ssandbox/containerfs.h"

ssandbox::abstruct_container_fs::abstruct_container_fs() {
    this->_mount_proc_flag = true;
    this->_mount_tmp_flag = true;
}

ssandbox::abstruct_container_fs::~abstruct_container_fs() {}