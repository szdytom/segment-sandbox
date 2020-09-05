// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_LIMITS_H
#define SSANDBOX_LIMITS_H

#include <future>
#include <string>
#include <vector>
#include <cstdlib>

namespace ssandbox {

class LimitsMgr {
public:
    void memory(unsigned long long limit);
    std::future<bool>& time(unsigned limit);
    void cpu(unsigned int limit);
    void network(bool limit);
    void release();
    void task(pid_t pid);

    LimitsMgr(std::string uid);
    ~LimitsMgr();

private:
    bool _watchTimeLimit();

    pid_t _pid;
    std::string _uid;

    unsigned int _time_limit;

    std::vector<ssandbox::CgroupUnit*> _used_cgroup;
};

}; // namespace ssandbox

#endif // SSANDBOX_LIMITS_H