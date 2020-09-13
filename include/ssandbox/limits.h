// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_LIMITS_H
#define SSANDBOX_LIMITS_H

#include <cstdlib>
#include <future>
#include <string>
#include <vector>
#include "ssandbox/cgroup.h"

namespace ssandbox {

class limits_manager {
public:
    void memory(unsigned long long limit);
    void time(unsigned limit);
    void cpu(unsigned int limit);
    void network(bool limit);
    void release();
    void task(pid_t pid);
    void wait();
    void set_uid(std::string uid);

    limits_manager();
    ~limits_manager();

private:
    void _watchTimeLimit();

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

    void set_uid(std::string uid);
    void apply(pid_t container_pid);
    void wait();

    void set_time_limit(unsigned int time);
    void set_cpu_limit(unsigned int cpu);
    void set_memory_limit(unsigned long long memory);

private:
    std::string _uid;
    limits_manager* _limiter;

    unsigned int _cpu;
    unsigned int _time;
    unsigned long long _memory;
};

}; // namespace ssandbox

#endif // SSANDBOX_LIMITS_H