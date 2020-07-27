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
    char *options = new char[4096];
    sprintf(options, "lowerdir=%s,upperdir=%s,workdir=%s", 
            cfg.lower_dir.c_str(), cfg.upper_dir.c_str(), cfg.workspace.c_str());

    mount("", cfg.point.c_str(), "overlay", 0, options);
    delete[] options;


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

    if (umount2("/tmp", MNT_FORCE))
        throw std::runtime_error("[Segment Sandbox - umount_containerfs()] Cannot unmount fs of tmp");
    
    if (umount2("/proc", MNT_FORCE))
        throw std::runtime_error("[Segment Sandbox - umount_containerfs()] Cannot unmount fs of proc");
}