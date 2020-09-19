// -*- C++ -*- Part of the Segment Sandbox Project

#include <string>
#include <fmt/core.h>
#include <seccomp.h>
#include <unistd.h>

#ifndef SSANDBOX_LIMITS_SYSCALL_H
#define SSANDBOX_LIMITS_SYSCALL_H

namespace ssandbox {

class seccomp_rules {
public:
    void load();
    scmp_filter_ctx get();

    static seccomp_rules* get_instance();

private:
    seccomp_rules();
    ~seccomp_rules();

    static seccomp_rules* _instance;

    std::vector<int> _syscall_limit_table;
};

void apply_seccomp_limits();

} // namespace ssandbox

#endif // SSANDBOX_LIMITS_SYSCALL_H