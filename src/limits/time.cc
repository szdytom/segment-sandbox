#include <future>
#include <string>
#include <thread>
#include <chrono>
#include <fmt/format.h>
#include <signal.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits.h"
#include "ssandbox/utils/process.h"

bool ssandbox::LimitsMgr::_watchTimeLimit() {
    const unsigned int wait_time_ms = 50U;
    const unsigned int extra_time = 500U;
    const auto limit = std::chrono::microseconds(this->_time_limit + extra_time);
    auto start_time_clock = std::chrono::steady_clock::now();

    while (true) {
        std::this_thread::sleep_for(std::chrono::microseconds(wait_time_ms));
        if (!ssandbox::utils::process::checkProcessAlive(this->_pid))
            return false;

        auto delta = std::chrono::steady_clock::now() - start_time_clock;
        if (delta > limit) {
            kill(this->_pid, SIGKILL);
            return true;
        }
    }
}

std::future<bool>& ssandbox::LimitsMgr::time(unsigned int limit) {
    this->_time_limit = limit;
    static auto surveillant = std::async([this] { return this->_watchTimeLimit(); });
    return surveillant;
}
