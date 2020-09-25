// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SANDBOX_H
#define SANDBOX_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <memory>
#include <string>
#include "ssandbox/containerfs.h"
#include "ssandbox/limits/resource.h"
#include "ssandbox/semaphore.h"

namespace ssandbox {

typedef int (*container_func_t)(void* arg);

struct sandbox_t {
    std::string uid;           /* an unique ID for this sandbox */
    int stack_size;            /* stack size of new program, in bytes */
    container_func_t function; /* function to run inside sandbox */
    void* func_args;           /* fnuction's args */
    std::string hostname;      /* hostname inside container */
    AbstructContainerFS* fs;   /* handler filesystem in container */
    limit_info_t limit_config; /* Resource Limit Config */
    bool enable_network;       /* Clone new network namespace or not */
};

struct run_result_t {
    std::chrono::milliseconds time;
    int exit_status;
};

struct _sandbox_prepar_info {
    ssandbox::sandbox_t* cfg;
    ssandbox::semaphore* semaphore;
    std::chrono::steady_clock::time_point start_time;
};

class container {
public:
    sandbox_t* cfg;
    void start();
    ssandbox::run_result_t wait();
    void stop();

private:
    pid_t _container_pid;
    _sandbox_prepar_info* prepar_config;
    std::unique_ptr<char[]> container_stack;

    void _clear();
};

} // namespace ssandbox

#endif /* SANDBOX_H */