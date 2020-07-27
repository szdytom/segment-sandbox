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

struct fsconfig_t {
    std::filesystem::path root;
    std::filesystem::path work;
};

} /* namespace ssandbox */

#endif /* CONTAINERFS_H */