#include <cerrno>
#include <cstring>
#include <ssandbox/sandbox.h>
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
    cfg->stack_size = 1024 * 1024; // 1MB
    cfg->hostname = "container";

    cfg->mnt_config.point = "/mnt/sandbox/merge";
    cfg->mnt_config.lower_dir = "/mnt/image";
    cfg->mnt_config.upper_dir = "/mnt/sandbox/upper";
    cfg->mnt_config.workspace = "/mnt/sandbox/work";
    cfg->mnt_config.mount_proc = true;
    cfg->mnt_config.mount_tmp = true;

    cfg->limit_config.cpu = -1;
    cfg->limit_config.time = 10000; // 10s
    cfg->limit_config.memory = -1; // unlimited

    printf("Outside\n");
    create_sandbox(cfg);
    printf("Returned to father!\n");
    return 0;
}