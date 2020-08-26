/**
 * sandbox.cc
 * Define of functions in sandbox.h
 *
 * public functions:
 * ssandbox::create_sandbox(std::shared_ptr<ssandbox::sandbox_t>)
 *
 * private functions:
 * entry_handle(void *cfg_ptr);
 */

#include "../include/sandbox.h"

/**
 * @brief Configure Settings inside container
 * @param cfg_ptr sandbox config
 * @return int the cfg->function return
 * 
 * Config settings inside container.
 * 1. Set Host Name
 * 2. Mount Filesystem
 */
int entry_handle(void *cfg_ptr) {
	std::shared_ptr<ssandbox::sandbox_t> cfg = *((std::shared_ptr<ssandbox::sandbox_t>*)cfg_ptr);
	sethostname(cfg->hostname.c_str(), cfg->hostname.size());

    ssandbox::mount_containerfs(cfg->mnt_config);
	int res = cfg->function(cfg->func_args);
    // ssandbox::umount_containerfs(cfg->mnt_config);

    return res;
}

/**
 * @brief Create A New Sandbox
 * @param cfg sandbox config
 * @throw std::runtime_error, in which case clone process failed
 * 
 * create a sandbox to run cfg->function.
*/
void ssandbox::create_sandbox(std::shared_ptr<ssandbox::sandbox_t> cfg) {
    /* create stack space for child to use */
    /* new will throw out a alloc_error if fail, so we don't need to handle nullptr */
    std::unique_ptr<char[]> container_stack(new char[cfg->stack_size]);
    char *container_stack_ptr = container_stack.get();

    int container_pid = clone((ssandbox::container_func)entry_handle, 
							  container_stack_ptr + cfg->stack_size, /* reverse memory */
                              SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWUSER | CLONE_NEWNS, 
							  (void*)(&cfg));

    if (container_pid == -1)
        /* clone process failed */
        throw std::runtime_error("[Segment Sandbox - create_sandbox()] Clone new process failed");

    waitpid(container_pid, nullptr, 0); /* wait for child to stop */

    /* unique_ptr frees memory */
}