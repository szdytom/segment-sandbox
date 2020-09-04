// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef CONTAINERFS_H
#define CONTAINERFS_H

#include <sys/mount.h>
#include <filesystem>
#include <memory>

namespace ssandbox {

struct MountInfo {
    /* will be mount to here in you host machine */
    std::filesystem::path point;
    /* Mount source in your host machine (Lower Directory) */
    std::filesystem::path lower_dir;
    /* Temp Working Dir for overlay */
    std::filesystem::path workspace;
    /* Upper Directory */
    std::filesystem::path upper_dir;
    
    /* An extra point to mount, will be mounted into /mnt inside container*/
    std::filesystem::path extra_point;

    /* If enabled, it will mount /proc */
    bool mount_proc;

    /* If enabled, it will mount /tmp */
    bool mount_tmp;
};

void mount_containerfs(MountInfo cfg);
void umount_containerfs(MountInfo cfg);

} /* namespace ssandbox */

#endif /* CONTAINERFS_H */