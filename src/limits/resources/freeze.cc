#include <string>
#include <fmt/core.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits/resource.h"

void ssandbox::limits_manager::freeze(bool limit) {
    auto cs = ssandbox::cgroup_subsystem("freezer");
    auto c = cs.create(fmt::format("ssandbox_{}", this->_uid));

    c->write("tasks", std::to_string(this->_pid));
    c->write("freezer.state", limit ? "FROZEN" : "THAWED");

    this->_used_cgroup.push_back(c);
}