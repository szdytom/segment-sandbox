#include "ssandbox/limits/syscall.h"

ssandbox::seccomp_rules* ssandbox::seccomp_rules::_instance = nullptr;

ssandbox::seccomp_rules::seccomp_rules() {}
ssandbox::seccomp_rules::~seccomp_rules() {}

ssandbox::seccomp_rules* ssandbox::seccomp_rules::get_instance() {
    if (ssandbox::seccomp_rules::_instance == nullptr)
        ssandbox::seccomp_rules::_instance = new ssandbox::seccomp_rules;

    return ssandbox::seccomp_rules::_instance;
}