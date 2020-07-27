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
	printf("exiting\n");
    return 0;
}

int main() {
	shared_ptr<sandbox_t> cfg(new sandbox_t);
	cfg->function = func;
	cfg->func_args = container_args;
	cfg->stack_size = 1024 * 1024; // 1MB
	cfg->hostname = "container";
    
    cfg->mnt_config.point = "/";
    cfg->mnt_config.mount_proc = true;
    cfg->mnt_config.mount_tmp = true;
	
	printf("Outside\n");
    try {
	    create_sandbox(cfg);
    } catch (runtime_error &err) {
        printf("Error [%d]: %s\n", errno, strerror(errno));
        printf("Error solved!\n");
    }
	printf("Returned to father!\n");
	return 0;
}