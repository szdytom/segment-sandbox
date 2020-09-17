#include "ssandbox/sandbox.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <future>
#include <stdexcept>
#include <fmt/core.h>
#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "ssandbox/limits/resource.h"
#include "ssandbox/semaphore.h"
#include "ssandbox/userns.h"
#include "ssandbox/utils/exceptions.h"

struct sandbox_prepar_info {
    ssandbox::sandbox_t* cfg;
    ssandbox::semaphore* semaphore;
};

/**
 * @brief Configure Settings inside container
 * @param cfg_ptr sandbox config
 * @return int the cfg->function return
 * 
 * Config settings inside container.
 * 1. Set Host Name
 * 2. Mount Filesystem
 */
int entry_handle(void* cfg_ptr) {
    auto prepar_cfg = (sandbox_prepar_info*)(cfg_ptr);
    auto cfg = prepar_cfg->cfg;

    sethostname(cfg->hostname.c_str(), cfg->hostname.size());

    cfg->fs->mount_all();

    /* Now it is prepared to run costum function, but we need to wait for the semaphore first */
    prepar_cfg->semaphore->wait();

    int res = cfg->function(cfg->func_args);
    return res;
}

/**
 * @brief Create A New Sandbox
 * @param cfg sandbox config
 * @throw ssandbox::exceptions::syscall_error, in which case clone process failed
 * 
 * create a sandbox to run cfg->function.
*/
void ssandbox::create_sandbox(std::shared_ptr<ssandbox::sandbox_t> cfg) {
    /* create stack space for child to use */
    /* new will throw out a alloc_error if fail, so we don't need to handle nullptr */
    std::unique_ptr<char[]> container_stack(new char[cfg->stack_size]);
    char* container_stack_ptr = container_stack.get();

    /* Set UID at different classes */
    cfg->fs->set_uid(cfg->uid);
    cfg->limit_config.set_uid(cfg->uid);

    auto prepar_config = new sandbox_prepar_info;
    prepar_config->cfg = cfg.get();
    prepar_config->semaphore = new ssandbox::semaphore;

    int clone_flags = SIGCHLD | CLONE_VM | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS;
    if (!cfg->enable_network)
        clone_flags |= CLONE_NEWNET;

    pid_t container_pid = clone((ssandbox::container_func_t)entry_handle,
                                container_stack_ptr + cfg->stack_size, /* reverse memory */
                                clone_flags,
                                (void*)prepar_config);

    if (container_pid == -1)
        /* clone process failed */
        throw ssandbox::exceptions::syscall_error(errno, "Clone new process failed", __FUNCTION__);

    /* set uid & gid map */
    auto user_ns_mgr = ssandbox::user_namespace_manager::get_instance();
    user_ns_mgr->set_uid_map(container_pid, 0, getuid(), 1);
    user_ns_mgr->set_gid_map(container_pid, 0, getgid(), 1);

    /* set limits */
    cfg->limit_config.apply(container_pid);

    /* send semaphore */
    prepar_config->semaphore->post(0);

    /* wait for child to stop */
    waitpid(container_pid, nullptr, 0);
    cfg->limit_config.wait();

    /* clear mounted fs */
    cfg->fs->umount_all();

    delete prepar_config->semaphore;
    delete prepar_config;
    /* unique_ptr frees memory */
}