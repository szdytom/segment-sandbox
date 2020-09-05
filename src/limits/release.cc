#include <string>
#include <fmt/format.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits.h"

void ssandbox::LimitsMgr::release() {
    this->wait();
    for (ssandbox::CgroupUnit* c : this->_used_cgroup) {
        c->remove();
        delete c;
    }

    this->_used_cgroup.clear();
}
