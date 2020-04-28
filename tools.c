/*
Define of functions in tools.h
*/

#include "tools.h"

/* log part start here */

/* Log error to stderr */
void log_error(char *funcname, char *format, ...) {
	va_list args; /* uncountable args ... */

	fprintf(stderr, "Error[%s]: ", funcname);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
}

/* Log warning to stderr */
void log_warning(char *funcname, char *format, ...) {
	va_list args; /* uncountable args ... */

	fprintf(stderr, "Warning[%s]: ", funcname);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
}

/* Log message to stderr */
void log_meaasge(char *funcname, char *format, ...) {
	va_list args; /* uncountable args ... */

	fprintf(stderr, "Message[%s]: ", funcname);
	vfprintf(stderr, format, args);
	fprintf(stderr, "\n");
}

/* log part end here */

/* Arithmetic part starts here */



/* Arithmetic part ends here */