// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_UTILS_PROCESS
#define SSANDBOX_UTILS_PROCESS

#include <sys/types.h>

namespace ssandbox {

namespace utils {

namespace process {

bool checkProcessAlive(pid_t pid);

} // namespace process

} // namespace utils

} // namespace ssandbox

#endif // SSANDBOX_UTILS_PROCESS