#include <string>
#include <fmt/core.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits/resource.h"

void ssandbox::limits_manager::freeze(bool limit) {
    ssandbox::cgroup_unit* c;

    bool flag = false;
    for (auto x : this->_used_cgroup) {
        if (x->get_subsys_type() == "freezer") {
            c = x;
            flag = true;
        }
    }

    if (!flag) {
        auto cs = ssandbox::cgroup_subsystem("freezer");
        c = cs.create(fmt::format("ssandbox_{}", this->_uid));
    }

    c->write("tasks", std::to_string(this->_pid));
    c->write("freezer.state", limit ? "FROZEN" : "THAWED");

    if (!flag)
        this->_used_cgroup.push_back(c);
}