/*
Tools for sandbox
*/

#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdarg.h>

/* Log part starts here */

void log_error(const char *funcname, const char *format, ...);
void log_warning(const char *funcname, const char *format, ...);
void log_message(const char *funcname, const char *format, ...);

/* Log part ends here */

#endif /* TOOLS_H */