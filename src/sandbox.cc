#include "ssandbox/sandbox.h"
#include <chrono>
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
#include "ssandbox/limits/syscall.h"
#include "ssandbox/semaphore.h"
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
 * 3. Set System Call Limits (seccomp)
 */
int entry_handle(void* cfg_ptr) {
    auto prepar_cfg = reinterpret_cast<ssandbox::_sandbox_prepar_info*>(cfg_ptr);
    auto cfg = prepar_cfg->cfg;

    sethostname(cfg->hostname.c_str(), cfg->hostname.size());
    cfg->fs->mount_all();
    ssandbox::apply_seccomp_limits();

    /* Now it is prepared to run costum function, but we need to wait for the semaphore first */
    prepar_cfg->lock->wait();

    prepar_cfg->start_time = std::chrono::steady_clock::now();
    return cfg->func();
}

void ssandbox::container::start() {
    /* create stack space for child to use */
    /* new will throw out a alloc_error if fail, so we don't need to handle nullptr */
    this->_container_stack.reset(new char[cfg->stack_size]);
    char* container_stack_ptr = _container_stack.get();

    /* Set UID in different classes */
    this->cfg->fs->set_uid(this->cfg->uid);

    /* prepar resource limiter */
    this->_limiter.reset(new ssandbox::limits_manager, [](ssandbox::limits_manager* x) {
        x->release();
        delete x;
    });

    this->cfg->limit_config.set_up(this->cfg->uid, this->_limiter);

    this->_prepar_config.reset(new ssandbox::_sandbox_prepar_info);
    this->_prepar_config->cfg = this->cfg;
    this->_prepar_config->lock.reset(new ssandbox::semaphore);

    int clone_flags = SIGCHLD | CLONE_VM | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS;
    if (!this->cfg->enable_network)
        clone_flags |= CLONE_NEWNET;

    this->_container_pid = clone(entry_handle, container_stack_ptr + cfg->stack_size, /* reverse memory */
                                 clone_flags, reinterpret_cast<void*>(this->_prepar_config.get()));

    if (this->_container_pid == -1)
        /* clone process failed */
        throw ssandbox::exceptions::syscall_error(errno, "Clone new process failed", __FUNCTION__);

    /* set uid & gid map */
    auto user_ns_mgr = ssandbox::user_namespace_manager::get_instance();
    user_ns_mgr->set_uid_map(this->_container_pid, 0, geteuid(), 1);
    user_ns_mgr->set_gid_map(this->_container_pid, 0, getegid(), 1);

    /* set limits */
    this->cfg->limit_config.apply(this->_container_pid);

    /* send semaphore */
    this->_prepar_config->lock->post(0);
}

ssandbox::run_result_t ssandbox::container::wait() {
    /* child exit status */
    int sstatus;

    /* wait for child to stop */
    waitpid(this->_container_pid, &sstatus, 0);

    /* get resource usages */
    ssandbox::run_result_t res;
    res.time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()
                                                                     - this->_prepar_config->start_time);
    res.exit_status = sstatus;

    /* clear others up */
    this->_clear();

    return res;
}

void ssandbox::container::stop() {
    /* kill container process */
    kill(this->_container_pid, SIGKILL);
    this->wait();
}

void ssandbox::container::_clear() {
    this->cfg->limit_config.wait();

    /* clear mounted fs */
    this->cfg->fs->umount_all();

    /* free memory inside unique_ptr */
    this->_container_stack.reset(nullptr);
}

void ssandbox::container::freeze() {
    this->_limiter->freeze();
}

void ssandbox::container::thaw() {
    this->_limiter->freeze(false);
}