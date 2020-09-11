#include "ssandbox/userns.h"
#include <cstdio>
#include <errno.h>
#include <fmt/core.h>
#include "ssandbox/utils/exceptions.h"

ssandbox::user_namespace_manager* ssandbox::user_namespace_manager::_instance = nullptr;

ssandbox::user_namespace_manager::user_namespace_manager() {}
ssandbox::user_namespace_manager::~user_namespace_manager() {}

ssandbox::user_namespace_manager* ssandbox::user_namespace_manager::get_instance() {
    if (ssandbox::user_namespace_manager::_instance == nullptr)
        ssandbox::user_namespace_manager::_instance = new ssandbox::user_namespace_manager();

    return ssandbox::user_namespace_manager::_instance;
}

void ssandbox::user_namespace_manager::_set_map(std::string file, int inside_id, int outside_id, int length) {
    FILE* mapfd = fopen(file.c_str(), "w");
    if (mapfd == nullptr)
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot open file '{}'", file), __FUNCTION__);

    fmt::print(mapfd, "{} {} {}", inside_id, outside_id, length);
    fclose(mapfd);
}

void ssandbox::user_namespace_manager::set_uid_map(pid_t pid, int inside_id, int outside_id, int length) {
    this->_set_map(fmt::format("/proc/{}/uid_map", pid), inside_id, outside_id, length);
}

void ssandbox::user_namespace_manager::set_gid_map(pid_t pid, int inside_id, int outside_id, int length) {
    this->_set_map(fmt::format("/proc/{}/gid_map", pid), inside_id, outside_id, length);
}