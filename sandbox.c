/*
Define of functions in sandbox.h
*/

#include "sandbox.h"
#include "tools.h"

int create_sandbox(sandbox_t *cfg) {
	/* create stack space for child to use */
	char *container_stack = (char *)malloc(cfg->stack_size);
	if (container_stack == NULL) {
		/* malloc failed */
		log_error(__FUNCTION__, "malloc container stack failed.");
		return -1;
	}
	container_stack += cfg->stack_size; /* reverse memory */

	int container_pid = clone(cfg->function, container_stack
		, SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID
		, cfg->func_args);

	if (container_pid == -1) {
		/* clone failed */
		log_error(__FUNCTION__, "clone new process failed.");
		return -1;
	}
	
	waitpid(container_pid, NULL, 0); /* wait for child to stop */
	
	/* free memory */
	container_stack -= cfg->stack_size; /* reserver it back */
	free(container_stack);

	return 0;
}