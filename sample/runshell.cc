#include <cerrno>
#include <cstring>
#include <memory>
#include <ssandbox/ssandbox.h>
#include <sys/wait.h>
#include <sys/unistd.h>
using namespace std;
using namespace ssandbox;

int func() {
    const char* container_args[] = {"/bin/sh", nullptr};

    printf("Inside container [%05d]!\n", getpid());

    char** xargs = (char**)container_args;
    printf("+%s\n", xargs[0]);

    if (execv(xargs[0], xargs)) {
        printf("ERR: [%d] %s\n", errno, strerror(errno));
    }

    printf("exiting\n");
    return 0;
}

int main() {
    // load seccomp limit profile
    seccomp_rules::get_instance()->load();

    auto cfg = make_shared<sandbox_t>();
    cfg->func = func;
    cfg->stack_size = 5 * 1024 * 1024; // 5MB
    cfg->hostname = "container";
    cfg->uid = "runshell";
    cfg->enable_network = false;

    auto container_fs = make_shared<readonly_container_fs>();
    container_fs->enable_proc();
    container_fs->enable_tmp();
    container_fs->set_image("/mnt/sandboxes/image");
    container_fs->set_workspace("/mnt/sandboxes/workspace");
    cfg->fs = container_fs;

    cfg->limit_config.set_cpu_limit(30);      // 30% on one core
    cfg->limit_config.set_time_limit(100000); // 100s(1min40s)
    cfg->limit_config.set_memory_limit(0);    // unlimited
    cfg->limit_config.set_fork_limit(10);     // at most fork 10 times (create 10 child process)

    printf("Outside\n");
    container c;
    c.cfg = cfg;
    c.start();
    auto res = c.wait();
    printf("Time: %ld\n", res.time.count());
    printf("Returned to father!\n");
    return 0;
}