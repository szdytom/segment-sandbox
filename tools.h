/*
Tools for sandbox
*/

#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdarg.h>

/* Log part starts here */

void log_error(char *funcname, char *format, ...);
void log_warning(char *funcname, char *format, ...);
void log_message(char *funcname, char *format, ...);

/* Log part ends here */

#endif /* TOOLS_H */