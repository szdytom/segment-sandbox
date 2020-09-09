#include "ssandbox/limits.h"
#include <exception>
#include <stdexcept>
#include <string>
#include <fmt/core.h>
#include "ssandbox/utils/exceptions.h"
#include "ssandbox/utils/process.h"

ssandbox::LimitsMgr::LimitsMgr() {
    this->_time_surveillant_mark = false;
}

ssandbox::LimitsMgr::~LimitsMgr() {
    this->release();
}

void ssandbox::LimitsMgr::task(pid_t pid) {
    if (!ssandbox::process::checkProcessAlive(pid))
        throw std::logic_error(ssandbox::exceptions::getSSErrorMsg(fmt::format("Process {} not found or already dead.", pid), __FUNCTION__));

    this->_pid = pid;
}

void ssandbox::LimitsMgr::set_uid(std::string uid) {
    this->_uid = uid;
}