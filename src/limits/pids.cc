#include <string>
#include <fmt/core.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits/resource.h"

void ssandbox::limits_manager::process(unsigned int limit) {
    auto cs = ssandbox::cgroup_subsystem("pids");
    auto c = cs.create(fmt::format("ssandbox_{}", this->_uid));

    c->write("pids.max", std::to_string(limit));
    c->write("tasks", std::to_string(this->_pid));

    this->_used_cgroup.push_back(c);
}
