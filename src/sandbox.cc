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
#include "ssandbox/limits.h"
#include "ssandbox/userns.h"
#include "ssandbox/utils/exceptions.h"

/**
 * @brief Configure Settings inside container
 * @param cfg_ptr sandbox config
 * @return int the cfg->function return
 * 
 * Config settings inside container.
 * 1. Set Host Name
 * 2. Mount Filesystem
 */
int ssandbox::entry_handle(void* cfg_ptr) {
    std::shared_ptr<ssandbox::sandbox_t> cfg = *((std::shared_ptr<ssandbox::sandbox_t>*)cfg_ptr);
    sethostname(cfg->hostname.c_str(), cfg->hostname.size());

    cfg->fs->mountAll();
    int res = cfg->function(cfg->func_args);
    return res;
}

/**
 * @brief Create A New Sandbox
 * @param cfg sandbox config
 * @throw ssandbox::utils::exceptions::syscall_error, in which case clone process failed
 * 
 * create a sandbox to run cfg->function.
*/
void ssandbox::create_sandbox(std::shared_ptr<ssandbox::sandbox_t> cfg) {
    /* create stack space for child to use */
    /* new will throw out a alloc_error if fail, so we don't need to handle nullptr */
    std::unique_ptr<char[]> container_stack(new char[cfg->stack_size]);
    char* container_stack_ptr = container_stack.get();

    /* Set UID at mount namespace */
    cfg->fs->setUID(cfg->uid);

    pid_t container_pid = clone((ssandbox::container_func)ssandbox::entry_handle,
                                container_stack_ptr + cfg->stack_size, /* reverse memory */
                                SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS,
                                (void*)(&cfg));

    if (container_pid == -1)
        /* clone process failed */
        throw ssandbox::utils::exceptions::syscall_error(errno, "Clone new process failed", __FUNCTION__);

    /* set uid & gid map */
    auto user_ns_mgr = ssandbox::UserNamespaceMgr::getInstance();
    user_ns_mgr->setUIDMap(container_pid, 0, getuid(), 1);
    user_ns_mgr->setGIDMap(container_pid, 0, getgid(), 1);

    /* set limits */
    LimitsMgr limiter(cfg->uid);
    limiter.task(container_pid);

    if (cfg->limit_config.cpu != -1)
        limiter.cpu(cfg->limit_config.cpu);

    if (cfg->limit_config.time != -1)
        limiter.time(cfg->limit_config.time);

    if (cfg->limit_config.memory != -1)
        limiter.memory(cfg->limit_config.memory);

    limiter.wait();
    waitpid(container_pid, nullptr, 0); /* wait for child to stop */

    /* clear mounted fs */
    cfg->fs->umountAll();

    /* unique_ptr frees memory */
}