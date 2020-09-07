#include "ssandbox/containerfs.h"

void ssandbox::AbstructContainerFS::mountAll() {
    if (this->_mount_tmp)
        this->mountTmp();

    if (this->_mount_proc)
        this->mountProc();
    
    this->mountMain();
    this->mountExtra();
}

void ssandbox::AbstructContainerFS::umountAll() {
    if (this->_mount_tmp)
        this->umountTmp();

    if (this->_mount_proc)
        this->umountProc();
    
    this->umountMain();
    this->umountExtra();
}