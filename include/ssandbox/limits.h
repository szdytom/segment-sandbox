// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_LIMITS_H
#define SSANDBOX_LIMITS_H

#include <cstdlib>
#include <future>
#include <string>
#include <vector>
#include "ssandbox/cgroup.h"

namespace ssandbox {

class LimitsMgr {
public:
    void memory(unsigned long long limit);
    void time(unsigned limit);
    void cpu(unsigned int limit);
    void network(bool limit);
    void release();
    void task(pid_t pid);
    void wait();

    LimitsMgr(std::string uid);
    ~LimitsMgr();

private:
    void _watchTimeLimit();

    pid_t _pid;
    std::string _uid;

    unsigned int _time_limit;
    bool _time_surveillant_mark;
    std::future<void> _time_surveillant;

    std::vector<ssandbox::CgroupUnit*> _used_cgroup;
};

}; // namespace ssandbox

#endif // SSANDBOX_LIMITS_H