#include "ssandbox/cgroup.h"
#include <fmt/core.h>
#include <cstdio>
#include <cerrno>
#include "ssandbox/utils/exceptions.h"

ssandbox::cgroup_subsystem::cgroup_subsystem() {}
ssandbox::cgroup_subsystem::~cgroup_subsystem() {}

ssandbox::cgroup_subsystem::cgroup_subsystem(std::string subsys_type) {
    this->set(subsys_type);
}

void ssandbox::cgroup_subsystem::set(std::string subsys_type) {
    std::filesystem::path subsys_path = ssandbox::cgroup_base;
    subsys_path /= subsys_type;
    if (!std::filesystem::exists(subsys_path))
        throw std::logic_error(ssandbox::exceptions::get_formated_ssandbox_errormsg(fmt::format("Cgroup Subsystem '{}' does not exists", subsys_type), __FUNCTION__));

    this->_subsys_type = subsys_type;
}

ssandbox::cgroup_unit* ssandbox::cgroup_subsystem::create(std::string unit_name) {
    auto res = new ssandbox::cgroup_unit(this->_subsys_type, unit_name);
    return res;
}