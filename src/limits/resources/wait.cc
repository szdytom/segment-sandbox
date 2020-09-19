#include <string>
#include <fmt/core.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits/resource.h"

void ssandbox::limits_manager::wait() {
    if (this->_time_surveillant_mark)
        this->_time_surveillant.wait();
    
    this->_time_surveillant_mark = false;
}
