/*
 * sandbox.h
 * The main header file of segment-sandbox.
 *
 * struct & classes & types:
 * ssandbox::sandbox_t
 * ssandbox::create_sandbox(std::shared_ptr<ssandbox::sandbox_t>)
 *
 * functions:
 * void create_sandbox(std::shared_ptr<sandbox_t>);
 *
 * See the define of these functions in ../src/sandbox.cc
 */

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
#include <memory>
#include <string>

#include "containerfs.h"

namespace ssandbox {

typedef int (*container_func)(void *arg);

struct sandbox_t {
    int stack_size;          /* stack size of new program, in bytes */
    container_func function; /* function to run inside sandbox */
    void *func_args;         /* fnuction's args */
    std::string hostname;    /* hostname inside container */
    MountInfo mnt_config;    /* Mount Info  */
};

void create_sandbox(std::shared_ptr<sandbox_t> cfg);

} // namespace ssandbox

#endif /* SANDBOX_H */