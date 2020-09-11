#include "ssandbox/semaphore.h"
#include <chrono>
#include <thread>
#include <fmt/core.h>

const unsigned int ssandbox::semaphore::_time = 50U;

ssandbox::semaphore::semaphore() {
    this->_mark = false;
}

ssandbox::semaphore::~semaphore() {}

void ssandbox::semaphore::post(int val) {
    this->_value = val;
    this->_mark = true;
}

void ssandbox::semaphore::wait() {
    while (!this->_mark) {
        std::this_thread::sleep_for(std::chrono::microseconds(ssandbox::semaphore::_time));
    }
}

bool ssandbox::semaphore::wait_for(unsigned int time_limit) {
    auto start_time = std::chrono::steady_clock::now();
    auto time_lim = std::chrono::microseconds(time_limit);

    while (!this->_mark) {
        std::this_thread::sleep_for(std::chrono::microseconds(ssandbox::semaphore::_time));

        auto delta = std::chrono::steady_clock::now() - start_time;
        if (delta > time_lim)
            return false;
    }

    return true;
}

int ssandbox::semaphore::get() {
    this->wait();
    return this->_value;
}