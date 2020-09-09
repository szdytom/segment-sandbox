#include "ssandbox/semaphore.h"
#include <chrono>

void ssandbox::semaphore::init() {
    this->_target.reset(new std::promise<int>());
    this->_future = this->_target->get_future();
}

void ssandbox::semaphore::post(int val) {
    this->_target->set_value(val);
}

void ssandbox::semaphore::wait() {
    this->_future.wait();
}

bool ssandbox::semaphore::wait_for(unsigned int time_limit) {
    return this->_future.wait_for(std::chrono::microseconds(time_limit)) == std::future_status::ready;
}

int ssandbox::semaphore::get() {
    return this->_future.get();
}