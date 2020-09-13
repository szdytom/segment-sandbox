#include <chrono>
#include <future>
#include <string>
#include <thread>
#include <fmt/core.h>
#include <signal.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/limits.h"
#include "ssandbox/utils/process.h"

void ssandbox::limits_manager::_watch_time_limit() {
    const unsigned int wait_time_ms = 50U;
    const unsigned int extra_time = 500U;
    const auto limit = std::chrono::milliseconds(this->_time_limit + extra_time);
    auto start_time_clock = std::chrono::steady_clock::now();

    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time_ms));
        if (!ssandbox::process::check_process_alive(this->_pid))
            return;

        auto delta = std::chrono::steady_clock::now() - start_time_clock;
        if (limit < delta) {
            kill(this->_pid, SIGKILL);
            return;
        }
    }
}

void ssandbox::limits_manager::time(unsigned int limit) {
    this->_time_limit = limit;
    this->_time_surveillant = std::async([this] { this->_watch_time_limit(); });
    this->_time_surveillant_mark = true;
}
