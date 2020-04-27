/*
Define of functions in sandbox.h
*/

#include "sandbox.h"

void create_sandbox(sandbox_t *cfg) {
	/* create stack space for child to use */
	char *container_stack = (char *)malloc(cfg->stack_size);
	container_stack += cfg->stack_size; /* reverse memory */

	int container_pid = clone(cfg->function, container_stack, 
		SIGCHLD | CLONE_NEWUTS | CLONE_NEWIPC, cfg->func_args);
	
	waitpid(container_pid, NULL, 0); /* wait for child to stop */
	
	/* free memory */
	container_stack -= cfg->stack_size;
	free(container_stack);
}