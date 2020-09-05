#include <string>
#include <fmt/format.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits.h"

void ssandbox::LimitsMgr::memory(unsigned long long limit) {
    auto cs = ssandbox::CgroupSubsystem("memory");
    auto c = cs.create(fmt::format("ssandbox_{}", this->_uid));

    c->write("memory.limit_in_bytes", std::to_string(limit));
    c->write("memory.kmem.limit_in_bytes", std::to_string(limit));
    c->write("tasks", std::to_string(this->_pid));

    this->_used_cgroup.push_back(c);
}
