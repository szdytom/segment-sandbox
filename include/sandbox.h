/*
 * The main header file of segment-sandbox.
 */

#ifndef SANDBOX_H
#define SANDBOX_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif /* _GNU_SOURCE */

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>

#include <sched.h>
#include <signal.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <string>
#include <memory>
#include <exception>

namespace ssandbox {

typedef int (*container_func)(void *arg);

struct sandbox_t {
    int stack_size;          /* stack size of new program, in bytes */
    container_func function; /* function to run inside sandbox */
    void *func_args;         /* fnuction's args */
	std::string hostname;    /* hostname inside container */
};

void create_sandbox(std::shared_ptr<sandbox_t> cfg);

} // namespace ssandbox

#endif /* SANDBOX_H */