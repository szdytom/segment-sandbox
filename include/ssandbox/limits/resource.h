// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_LIMITS_H
#define SSANDBOX_LIMITS_H

#include <cstdlib>
#include <future>
#include <string>
#include <vector>
#include <memory>
#include "ssandbox/cgroup.h"

namespace ssandbox {

class limits_manager {
public:
    void memory(unsigned long long limit);
    void time(unsigned limit);
    void cpu(unsigned int limit);
    void process(unsigned int limit);
    void freeze(bool limit = true);

    void release();
    void task(pid_t pid);
    void wait();
    void set_uid(const std::string& uid);

    limits_manager();
    ~limits_manager();

private:
    void _watch_time_limit();

    pid_t _pid;
    std::string _uid;

    unsigned int _time_limit;
    bool _time_surveillant_mark;
    std::future<void> _time_surveillant;

    std::vector<ssandbox::cgroup_unit*> _used_cgroup;
};

class limit_info_t {
public:
    limit_info_t();
    ~limit_info_t();

    void set_up(const std::string& uid, std::shared_ptr<limits_manager> mgr);
    void apply(pid_t container_pid);
    void wait();

    void set_time_limit(unsigned int time);
    void set_cpu_limit(unsigned int cpu);
    void set_memory_limit(unsigned long long memory);
    void set_fork_limit(unsigned int process);

private:
    void _not_applied_required(std::string function_name);

    std::string _uid;
    std::shared_ptr<limits_manager> _limiter;

    unsigned int _cpu;
    unsigned int _time;
    unsigned long long _memory;
    unsigned int _process;

    bool _limits_applied;
};

}; // namespace ssandbox

#endif // SSANDBOX_LIMITS_H