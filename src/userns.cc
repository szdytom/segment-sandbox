#include "ssandbox/userns.h"
#include <cstdio>
#include <errno.h>
#include <fmt/core.h>
#include "ssandbox/utils/exceptions.h"

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
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot open file '{}'", file), __FUNCTION__);

    fmt::print(mapfd, "{} {} {}", inside_id, outside_id, length);
    fclose(mapfd);
}

void ssandbox::UserNamespaceMgr::setUIDMap(pid_t pid, int inside_id, int outside_id, int length) {
    this->setMap(fmt::format("/proc/{}/uid_map", pid), inside_id, outside_id, length);
}

void ssandbox::UserNamespaceMgr::setGIDMap(pid_t pid, int inside_id, int outside_id, int length) {
    this->setMap(fmt::format("/proc/{}/gid_map", pid), inside_id, outside_id, length);
}