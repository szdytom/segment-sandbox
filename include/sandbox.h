/*
The main header file of segment-sandbox.
*/
#ifndef SANDBOX_H
#define SANDBOX_H

#define _GNU_SOURCE
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sched.h>
#include <signal.h>
#include <unistd.h>

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*container_func)(void *arg);

typedef struct {
    char *work_dir;   /* mount namespace to here */
    char *rootfs_dir; /* mount namespace from here */

    int stack_size;          /* stack size of new program, in bytes */
    container_func function; /* function to run inside sandbox */
    void *func_args;         /* fnuction's args */
} sandbox_t;

int create_sandbox(sandbox_t *cfg);

#endif /* SANDBOX_H */