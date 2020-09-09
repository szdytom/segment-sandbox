// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SANDBOX_H
#define SANDBOX_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <memory>
#include <string>
#include "ssandbox/containerfs.h"
#include "ssandbox/limits.h"

namespace ssandbox {

typedef int (*container_func)(void* arg);

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
    LimitsMgr* _limiter;

    unsigned int _cpu;
    unsigned int _time;
    unsigned long long _memory;
};

struct sandbox_t {
    std::string uid;           /* an unique ID for this sandbox */
    int stack_size;            /* stack size of new program, in bytes */
    container_func function;   /* function to run inside sandbox */
    void* func_args;           /* fnuction's args */
    std::string hostname;      /* hostname inside container */
    AbstructContainerFS* fs;   /* handler filesystem in container */
    limit_info_t limit_config; /* Resource Limit Config */
};

void create_sandbox(std::shared_ptr<sandbox_t> cfg);

} // namespace ssandbox

#endif /* SANDBOX_H */