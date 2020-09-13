#include <fmt/core.h>
#include "ssandbox/limits.h"
#include "ssandbox/utils/exceptions.h"

ssandbox::limit_info_t::limit_info_t() {
    this->_limiter = new limits_manager;

    this->_cpu = -1;
    this->_memory = -1;
    this->_time = -1;
    this->_process = -1;

    this->_limits_applied = false;
}

ssandbox::limit_info_t::~limit_info_t() {
    this->_limiter->release();
    delete this->_limiter;
}

void ssandbox::limit_info_t::set_uid(std::string uid) {
    this->_uid = uid;
    this->_limiter->set_uid(this->_uid);
}

void ssandbox::limit_info_t::apply(pid_t container_pid) {
    this->_limits_applied = true;
    this->_limiter->task(container_pid);

    if (this->_cpu >= 0)
        this->_limiter->cpu(this->_cpu);

    if (this->_time >= 0)
        this->_limiter->time(this->_time);

    if (this->_memory >= 0)
        this->_limiter->memory(this->_memory);

    if (this->_process >= 1)
        this->_limiter->process(this->_process);
}

void ssandbox::limit_info_t::wait() {
    if (!this->_limits_applied)
        throw std::logic_error(ssandbox::exceptions::get_formated_ssandbox_errormsg("You must apply limits before wait for response", __FUNCTION__));

    this->_limiter->wait();
}

void ssandbox::limit_info_t::set_time_limit(unsigned int time) {
    this->_not_applied_required(__FUNCTION__);
    this->_time = time;
}

void ssandbox::limit_info_t::set_cpu_limit(unsigned int cpu) {
    this->_not_applied_required(__FUNCTION__);
    this->_cpu = cpu;
}

void ssandbox::limit_info_t::set_memory_limit(unsigned long long memory) {
    this->_not_applied_required(__FUNCTION__);
    this->_memory = memory;
}

void ssandbox::limit_info_t::set_fork_limit(unsigned int process) {
    this->_not_applied_required(__FUNCTION__);
    this->_process = process;
}

void ssandbox::limit_info_t::_not_applied_required(std::string function_name) {
    if (this->_limits_applied)
        throw std::logic_error(ssandbox::exceptions::get_formated_ssandbox_errormsg("You cannot change settings after it is applied", function_name));
}