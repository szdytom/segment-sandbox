/**
 * sandbox.cc
 * Define of functions in userns.h
 *
 * public functions:
 * ssandbox::create_sandbox(std::shared_ptr<ssandbox::sandbox_t>)
 *
 * 
 */

#include "ssandbox/userns.h"
#include <cstdio>
#include <errno.h>
#include <fmt/core.h>

ssandbox::UserNamespaceMgr* ssandbox::UserNamespaceMgr::_instance = nullptr;

ssandbox::UserNamespaceMgr::UserNamespaceMgr() {}
ssandbox::UserNamespaceMgr::~UserNamespaceMgr() {}

ssandbox::UserNamespaceMgr* ssandbox::UserNamespaceMgr::getInstance() {
    if (ssandbox::UserNamespaceMgr::_instance == nullptr)
        ssandbox::UserNamespaceMgr::_instance = new ssandbox::UserNamespaceMgr();
    
    return ssandbox::UserNamespaceMgr::_instance;
}

void ssandbox::UserNamespaceMgr::setMap(std::string file, int inside_id, int outside_id, int length) {
    FILE* mapfd = fopen(file.c_str(), "w");
    if (mapfd == nullptr)
        throw std::runtime_error(fmt::format("[Segment Sandbox - {}] Cannot open file '{}': [{}] {}", __FUNCTION__, file, errno, strerror(errno)));

    fmt::print(mapfd, "{} {} {}", inside_id, outside_id, length);
    fclose(mapfd);
}

void ssandbox::UserNamespaceMgr::setUIDMap(pid_t pid, int inside_id, int outside_id, int length) {
    this->setMap(fmt::format("/proc/{}/uid_map", pid), inside_id, outside_id, length);
}

void ssandbox::UserNamespaceMgr::setGIDMap(pid_t pid, int inside_id, int outside_id, int length) {
    this->setMap(fmt::format("/proc/{}/gid_map", pid), inside_id, outside_id, length);
}