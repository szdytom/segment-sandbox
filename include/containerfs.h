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

class FileSystemConfig {
    public:
    FileSystemConfig() {}
    virtual ~FileSystemConfig() = 0;
    virtual void mount() = 0;
    virtual void chroot() = 0;
};

} /* namespace ssandbox */

#endif /* CONTAINERFS_H */