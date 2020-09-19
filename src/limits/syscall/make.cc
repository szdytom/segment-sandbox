#include <seccomp.h>
#include "ssandbox/limits/syscall.h"

scmp_filter_ctx ssandbox::seccomp_rules::get() {
    scmp_filter_ctx res = seccomp_init(SCMP_ACT_ALLOW);
    for (int x : this->_syscall_limit_table) {
        seccomp_rule_add(res, SCMP_ACT_KILL, x, 0);
    }

    return res;
}