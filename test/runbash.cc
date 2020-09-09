#include <cerrno>
#include <cstring>
#include <ssandbox/ssandbox.h>
#include <unistd.h>
using namespace std;
using namespace ssandbox;

const char* container_args[] = {
    "/bin/bash",
    NULL};

int func(void* args) {
    printf("Inside countainer [%05d]!\n", getpid());

    char** xargs = (char**)args;
    printf("+%s\n", xargs[0]);
    execv(xargs[0], xargs);
    printf("Err [%d]: %s\n", errno, strerror(errno));
    printf("exiting\n");
    return 0;
}

int main() {
    shared_ptr<sandbox_t> cfg(new sandbox_t);
    cfg->function = func;
    cfg->func_args = container_args;
    cfg->stack_size = 5 * 1024 * 1024; // 5MB
    cfg->hostname = "container";
    cfg->uid = "test";

    auto container_fs = new OverlayContainerFS();
    container_fs->enableProc();
    container_fs->enableTmp();
    container_fs->setImage("/mnt/image");
    container_fs->setWorkspace("/mnt/ssandbox");
    cfg->fs = container_fs;

    cfg->limit_config.set_cpu_limit(30);      // 30% on one core
    cfg->limit_config.set_time_limit(100000); // 100s (1min40s)
    cfg->limit_config.set_memory_limit(-1);   // unlimited

    printf("Outside\n");
    create_sandbox(cfg);
    printf("Returned to father!\n");

    delete container_fs;
    return 0;
}