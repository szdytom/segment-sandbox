#include "ssandbox/cgroup.h"
#include <fmt/core.h>
#include <cstdio>
#include <cerrno>
#include "ssandbox/utils/exceptions.h"

ssandbox::CgroupSubsystem::CgroupSubsystem() {}
ssandbox::CgroupSubsystem::~CgroupSubsystem() {}

ssandbox::CgroupSubsystem::CgroupSubsystem(std::string subsys_type) {
    this->set(subsys_type);
}

void ssandbox::CgroupSubsystem::set(std::string subsys_type) {
    std::filesystem::path subsys_path = ssandbox::cgroup_base;
    subsys_path /= subsys_type;
    if (!std::filesystem::exists(subsys_path))
        throw std::logic_error(fmt::format("[Segment Sandbox - {}] Cgroup Subsystem '{}' does not exists", __FUNCTION__, subsys_type));

    this->_subsys_type = subsys_type;
}

ssandbox::CgroupUnit* ssandbox::CgroupSubsystem::create(std::string unit_name) {
    auto res = new ssandbox::CgroupUnit(this->_subsys_type, unit_name);
    return res;
}