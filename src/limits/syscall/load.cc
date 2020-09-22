#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <seccomp.h>
#include "ssandbox/limits/syscall.h"
#include "ssandbox/utils/exceptions.h"
#include "ssandbox/utils/listfile.h"

void ssandbox::seccomp_rules::load(std::filesystem::path profile_path) {
    ssandbox::io::list_file_reader profile(profile_path.string());
    auto profile_content = profile.read();

    this->_syscall_limit_table.clear();
    for (auto x : profile_content) {
        auto syscall_id = seccomp_syscall_resolve_name(x.c_str());
        if (syscall_id == __NR_SCMP_ERROR)
            throw std::logic_error(ssandbox::exceptions::error_msg(fmt::format("Syscall '{}' not found", x), __FUNCTION__));

        this->_syscall_limit_table.push_back(seccomp_syscall_resolve_name(x.c_str()));
    }
}