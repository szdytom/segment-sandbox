/*
Define of functions in sandbox.h
*/

#include "../include/sandbox.h"

/**
 * @brief Configure Settings inside container
 * @param cfg sandbox config
 * @return int the cfg->function return
 * 
 * Not public.
 * Config settings inside container.
 * 1. Set Host Name
 * 2. 
 */

/**
 * @brief Create A New Sandbox
 * @param cfg sandbox config
 * @throw std::runtime_error, in which case clone process failed
 * 
 * create a sandbox to run cfg->function.
*/
void create_sandbox(std::shared_ptr<ssandbox::sandbox_t> cfg) {
    /* create stack space for child to use */
    /* new will throw out a alloc_error if fail, so we don't need to handle nullptr */
    std::unique_ptr<char[]> container_stack(new char[cfg->stack_size]);
    char *container_stack_ptr = container_stack.get();

    int container_pid = clone(cfg->function, container_stack_ptr + cfg->stack_size /* reverse memory */,
                              SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID, cfg->func_args);

    if (container_pid == -1)
        /* clone process failed */
        throw std::runtime_error("[Segment Sandbox - create_sandbox()] Clone new process failed");

    waitpid(container_pid, nullptr, 0); /* wait for child to stop */

    /* unique_ptr frees memory */
}