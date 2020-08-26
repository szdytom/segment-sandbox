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
#include <errno.h>

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
    std::string options;
    options = "lowerdir=" + cfg.lower_dir.native() + ",upperdir=" 
            + cfg.upper_dir.native() + ",workdir=" + cfg.workspace.native();

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