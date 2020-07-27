/**
 * containerfs.cc
 * Define of functions in containerfs.h
 *
 * public functions:
 * void ssandbox::mount_containerfs(std::shared_ptr<ssandbox::MountInfo>)
 *
 */

#include <exception>
#include <string>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/containerfs.h"

/**
 * @brief Mount filesystem into the continaer
 * @param cfg mount info & config
 * 
 * Mount filesystem inside container
 * It mount overlayfs on root
 * And it will switch point '/' there
*/
void ssandbox::mount_containerfs(ssandbox::MountInfo cfg) {
    std::string options;
    options = "lowerdir=" + cfg.lower_dir.native() + ",upperdir=" 
            + cfg.upper_dir.native() + ",workdir=" + cfg.workspace.native();

    if (mount("overlay", cfg.point.c_str(), "overlay", 0, options.c_str()))
        throw std::runtime_error("[Segment Sandbox - mount_containerfs()] Cannot mount overlayfs");

    /* Now main fs are correctly mounted, let chroot now.*/
    if (chdir(cfg.point.c_str())) 
        throw std::runtime_error("[Segment Sandbox - mount_containerfs()] Cannot change working point.");
    
    if (chroot("./"))
        throw std::runtime_error("[Segment Sandbox - mount_containerfs()] Cannot change root mount point('/').");

    if (cfg.mount_proc) {
        mkdir("/proc", 0);
        if (mount("proc", "/proc", "proc", 0, nullptr)) 
            throw std::runtime_error("[Segment Sandbox - mount_containerfs()] Cannot mount fs of proc.");
    }

    if (cfg.mount_tmp) { 
        mkdir("/tmp", 0);
        if (mount("tmpfs", "/tmp", "tmpfs", 0, nullptr)) 
            throw std::runtime_error("[Segment Sandbox - mount_containerfs()] Cannot mount fs of tmp.");
    }
}

/**
 * @brief Unmount filesystem in the continaer
 * @param cfg mount info & config
 * @throw std::runtime_error, in which case umount failed
 * 
 * Unmount filesystem inside container
 * It unmount overlayfs and other VFS inside container
 * And it will switch point '/' back
*/
void ssandbox::umount_containerfs(ssandbox::MountInfo cfg) {
    if (umount2(cfg.point.c_str(), MNT_FORCE))
        throw std::runtime_error("[Segment Sandbox - umount_containerfs()] Cannot unmount fs of overlay.");

    if (cfg.mount_tmp && umount2("/tmp", MNT_FORCE))
        throw std::runtime_error("[Segment Sandbox - umount_containerfs()] Cannot unmount fs of tmp");
    
    if (cfg.mount_proc && umount2("/proc", MNT_FORCE))
        throw std::runtime_error("[Segment Sandbox - umount_containerfs()] Cannot unmount fs of proc");
}