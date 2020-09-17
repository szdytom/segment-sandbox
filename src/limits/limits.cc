#include "ssandbox/limits/resource.h"
#include <exception>
#include <stdexcept>
#include <string>
#include <fmt/core.h>
#include "ssandbox/utils/exceptions.h"
#include "ssandbox/utils/process.h"

ssandbox::limits_manager::limits_manager() {
    this->_time_surveillant_mark = false;
}

ssandbox::limits_manager::~limits_manager() {
    this->release();
}

void ssandbox::limits_manager::task(pid_t pid) {
    if (!ssandbox::process::check_process_alive(pid))
        throw std::logic_error(ssandbox::exceptions::get_formated_ssandbox_errormsg(fmt::format("Process {} not found or already dead.", pid), __FUNCTION__));

    this->_pid = pid;
}

void ssandbox::limits_manager::set_uid(std::string uid) {
    this->_uid = uid;
}