// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SANDBOX_H
#define SANDBOX_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <functional>
#include <memory>
#include <string>
#include "ssandbox/containerfs.h"
#include "ssandbox/limits/resource.h"
#include "ssandbox/semaphore.h"

namespace ssandbox {

struct sandbox_t {
    std::string uid;                         /* an unique ID for this sandbox */
    int stack_size;                          /* stack size of new program, in bytes */
    std::function<int(void)> func;           /* function to run inside sandbox */
    std::string hostname;                    /* hostname inside container */
    std::shared_ptr<AbstructContainerFS> fs; /* handler filesystem in container */
    limit_info_t limit_config;               /* Resource Limit Config */
    bool enable_network;                     /* Clone new network namespace or not */
};

struct run_result_t {
    std::chrono::milliseconds time;
    int exit_status;
};

struct _sandbox_prepar_info {
    std::shared_ptr<sandbox_t> cfg;
    std::shared_ptr<ssandbox::semaphore> lock;
    std::chrono::steady_clock::time_point start_time;
};

class container {
public:
    void start();
    run_result_t wait();
    void stop();

    void freeze();
    void thaw();

private:
    pid_t _container_pid;
    std::shared_ptr<_sandbox_prepar_info> _prepar_config;
    std::shared_ptr<limits_manager> _limiter;
    std::unique_ptr<char[]> _container_stack;

    void _clear();

public:
    std::shared_ptr<sandbox_t> cfg;
};

} // namespace ssandbox

#endif /* SANDBOX_H */