/**
 * containerfs.h
 *
 * This file is about mount filesystem inside container
 *
 * 
 */

#ifndef CONTAINERFS_H
#define CONTAINERFS_H

#include <filesystem>

namespace ssandbox {

class MountInfo {
    /* will be mount to here in you host machine */
    std::filesystem::path work;
    /* Mount source in your host machine */
    std::filesystem::path root_mount_point;
    
    /* An extra point to mount, will be mounted into /mnt inside container*/
    std::filesystem::path extra_point;
    
    bool mount_proc;
    bool mount_tmp;
};

} /* namespace ssandbox */

#endif /* CONTAINERFS_H */