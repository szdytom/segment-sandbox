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

void create_sandbox(std::shared_ptr<sandbox_t> cfg);

} // namespace ssandbox

#endif /* SANDBOX_H */