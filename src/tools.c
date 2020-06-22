/*
Define of functions in tools.h
*/

#include "../include/tools.h"

/* log part start here */

/* Log error to stderr */
void log_error(const char *funcname, const char *format, ...) {
    va_list args; /* uncountable args ... */

    fprintf(stderr, "Error[%s]: ", funcname);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
}

/* Log warning to stderr */
void log_warning(const char *funcname, const char *format, ...) {
    va_list args; /* uncountable args ... */

    fprintf(stderr, "Warning[%s]: ", funcname);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
}

/* Log message to stderr */
void log_meaasge(const char *funcname, const char *format, ...) {
    va_list args; /* uncountable args ... */

    fprintf(stderr, "Message[%s]: ", funcname);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
}

/* log part end here */

/* Arithmetic part starts here */

/* Arithmetic part ends here */