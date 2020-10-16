#include <cerrno>
#include <cstring>
#include <ssandbox/ssandbox.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
using namespace ssandbox;

const char* container_args[] = {
    "/bin/bash",
    NULL};

int func(void* args) {
    printf("Inside container [%05d]!\n", getpid());

    char** xargs = (char**)args;
    printf("+%s\n", xargs[0]);

    printf("Inside fork [%05d]!\n", getpid());
    execv(xargs[0], xargs);

    printf("exiting\n");
    return 0;
}

int main() {
    // load seccomp limit profile
    ssandbox::seccomp_rules::get_instance()->load();

    auto cfg = new sandbox_t;
    cfg->function = func;
    cfg->func_args = container_args;
    cfg->stack_size = 5 * 1024 * 1024; // 5MB
    cfg->hostname = "container";
    cfg->uid = "runbash";
    cfg->enable_network = false;

    auto container_fs = new readonly_container_fs();
    container_fs->enable_proc();
    container_fs->enable_tmp();
    container_fs->set_image("sandboxes/image");
    container_fs->set_workspace("sandboxes/workspace");
    cfg->fs = container_fs;

    cfg->limit_config.set_cpu_limit(30);      // 30% on one core
    cfg->limit_config.set_time_limit(100000); // 100s (1min40s)
    cfg->limit_config.set_memory_limit(-1);   // unlimited
    cfg->limit_config.set_fork_limit(3);      // at most fork 3 times (create 3 child process)

    printf("Outside\n");
    ssandbox::container c;
    c.cfg = cfg;
    c.start();
    auto res = c.wait();
    printf("Time: %ld\n", res.time.count());
    printf("Returned to father!\n");

    delete container_fs;
    return 0;
}