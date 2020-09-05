// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SANDBOX_H
#define SANDBOX_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sched.h>
#include <signal.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <exception>
#include <string>

#include "ssandbox/containerfs.h"

namespace ssandbox {

typedef int (*container_func)(void* arg);

struct sandbox_limit_t {
    unsigned int cpu;
    unsigned int time;
    unsigned long long memory;
};

struct sandbox_t {
    std::string uid;              /* an unique ID for this sandbox */
    int stack_size;               /* stack size of new program, in bytes */
    container_func function;      /* function to run inside sandbox */
    void* func_args;              /* fnuction's args */
    std::string hostname;         /* hostname inside container */
    MountInfo mnt_config;         /* Mount Config */
    sandbox_limit_t limit_config; /* Resource Limit Config */
};

void create_sandbox(std::shared_ptr<sandbox_t> cfg);
int entry_handle(void* cfg_ptr);

} // namespace ssandbox

#endif /* SANDBOX_H */