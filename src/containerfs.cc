/**
 * containerfs.cc
 * Define of functions in containerfs.h
 *
 * public functions:
 * void ssandbox::mount_containerfs(std::shared_ptr<ssandbox::MountInfo>)
 * void ssandbox::umount_containerfs(std::shared_ptr<ssandbox::MountInfo>)
 */

#include "ssandbox/containerfs.h"
#include <exception>
#include <string>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <fmt/core.h>

/**
 * @brief Mount filesystem into the continaer
 * @param cfg mount info & config
 * 
 * Mount filesystem inside container
 * It mount overlayfs on root
 * And it will switch point '/' there
*/
void ssandbox::mount_containerfs(ssandbox::MountInfo cfg) {
    std::string options(fmt::format("lowerdir={},upperdir={},workdir={}", cfg.lower_dir.native(), cfg.upper_dir.native(), cfg.workspace.native()));

    if (mount("overlay", cfg.point.c_str(), "overlay", 0, options.c_str()))
        throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot mount overlayfs: [{}] {}", __FUNCTION__, errno, strerror(errno)));

    /* Now main fs are correctly mounted, let's chroot now. */
    if (chdir(cfg.point.c_str()))
        throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot change working point: [{}] {}", __FUNCTION__, errno, strerror));

    if (chroot("./"))
        throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot change root mount point: [{}] {}", __FUNCTION__, errno, strerror(errno)));

    if (cfg.mount_proc) {
        if (mkdir("/proc", S_IRWXU | S_IRWXG | S_IRWXO))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot make /proc for mount: [{}] {}", __FUNCTION__, errno, strerror(errno)));

        if (mount("proc", "/proc", "proc", 0, nullptr))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot mount fs of proc: [{}] {}", __FUNCTION__, errno, strerror(errno)));
    }

    if (cfg.mount_tmp) {
        if (mkdir("/tmp", S_IRWXU | S_IRWXG | S_IRWXO))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot make /proc for mount: [{}] {}", __FUNCTION__, errno, strerror(errno)));

        if (mount("tmpfs", "/tmp", "tmpfs", 0, nullptr))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot mount fs of tmp: [{}] {}", __FUNCTION__, errno, strerror(errno)));
    }
}

/**
 * @brief Unmount filesystem
 * @param cfg mount info & config
 * 
 * Umount filesystem from the container.
 * This lead to clean filesystem with no extra files inside container.
 * The root point will be switched back automatically.
*/
void ssandbox::umount_containerfs(ssandbox::MountInfo cfg) {
    /* tmp & proc filesystems must be umounted correctly before umounting overlayfs or else 'target is busy' is returned.*/

    if (cfg.mount_tmp) {
        std::string tmppath((cfg.point / "tmp").native());
        if (umount2(tmppath.c_str(), MNT_FORCE))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot umount fs of tmp: [{}] {}", __FUNCTION__, errno, strerror(errno)));
        
        if (rmdir(tmppath.c_str()))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Connot remove directory /tmp: [{}] {}", __FUNCTION__, errno, strerror(errno)));
    }
    
    if (cfg.mount_proc) {
        std::string proc_path((cfg.point / "proc").native());
        if (umount2(proc_path.c_str(), MNT_FORCE))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot umount fs of proc: [{}] {}", __FUNCTION__, errno, strerror(errno)));
        
        if (rmdir(proc_path.c_str()))
            throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Connot remove directory /proc: [{}] {}", __FUNCTION__, errno, strerror(errno)));
    }

    /* Now all other are umounted, overlay is no longer busy. It can be umounted right now. */
    if (umount2(cfg.point.c_str(), MNT_FORCE))
        throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot umount fs of overlay: [{}] {}", __FUNCTION__, errno, strerror(errno)));
}