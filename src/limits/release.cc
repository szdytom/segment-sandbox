#include <string>
#include <fmt/core.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits/resource.h"

void ssandbox::limits_manager::release() {
    this->wait();
    for (ssandbox::cgroup_unit* c : this->_used_cgroup) {
        c->remove();
        delete c;
    }

    this->_used_cgroup.clear();
}
