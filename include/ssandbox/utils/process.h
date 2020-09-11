// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_UTILS_PROCESS
#define SSANDBOX_UTILS_PROCESS

#include <sys/types.h>

namespace ssandbox {

namespace process {

bool check_process_alive(pid_t pid);

} // namespace process

} // namespace ssandbox

#endif // SSANDBOX_UTILS_PROCESS