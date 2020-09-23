#include <cerrno>
#include <seccomp.h>
#include "ssandbox/limits/syscall.h"

scmp_filter_ctx ssandbox::seccomp_rules::get() {
    scmp_filter_ctx res = seccomp_init(SCMP_ACT_ALLOW);
    for (int x : this->_syscall_limit_table) {
        if (x == SCMP_SYS(clone))
            seccomp_rule_add(res, SCMP_ACT_ALLOW, x, 1, SCMP_A0(scmp_compare::SCMP_CMP_MASKED_EQ, 2114060288, 0));
        else
            seccomp_rule_add(res, SCMP_ACT_ERRNO(EPERM), x, 0);
    }

    return res;
}