#include "../include/sandbox.h"
#include <cerrno>
using namespace std;
using namespace ssandbox;

const char* container_args[] = {
	"/bin/bash",
	NULL
};

int func(void *args) {
	printf("Inside countainer [%05d]!\n", getpid());

	char **xargs = (char**)args;
	printf("+%s\n", xargs[0]);
	execv(xargs[0], xargs);
    printf("Err [%d]", errno);
	printf("exiting\n");
    return 0;
}

int main() {
	shared_ptr<sandbox_t> cfg(new sandbox_t);
	cfg->function = func;
	cfg->func_args = container_args;
	cfg->stack_size = 1024 * 1024; // 1MB
	cfg->hostname = "container";

    cfg->mnt_config.point = "/rootfs/merge";
    cfg->mnt_config.lower_dir = "/rootfs/lower";
    cfg->mnt_config.upper_dir = "/rootfs/upper";
    cfg->mnt_config.workspace = "/rootfs/work";
    cfg->mnt_config.mount_proc = true;
    cfg->mnt_config.mount_tmp = true;
	
	printf("Outside\n");
	create_sandbox(cfg);
	printf("Returned to father!\n");
	return 0;
}