#include <exception>
#include <memory>
#include <stdexcept>
#include <string>
#include <seccomp.h>
#include "ssandbox/limits/syscall.h"
#include "ssandbox/utils/exceptions.h"
#include "ssandbox/utils/listfile.h"
#include "ssandbox/global_config.h"

void ssandbox::seccomp_rules::load() {
    auto global_cfg = ssandbox::global_config::get_instance();
    auto seccomp_profile = *(std::shared_ptr<std::string>*)global_cfg->get_field("seccomp_profile");
    if (seccomp_profile == nullptr) {
        seccomp_profile = std::make_shared<std::string>("/etc/ssandbox/seccomp.list");
        global_cfg->set_feild("seccomp_profile", &seccomp_profile);
    }

    ssandbox::io::list_file_reader profile(seccomp_profile->c_str());
    auto profile_content = profile.read();

    this->_syscall_limit_table.clear();
    for (auto x : profile_content) {
        auto syscall_id = seccomp_syscall_resolve_name(x.c_str());
        if (syscall_id == __NR_SCMP_ERROR)
            throw std::logic_error(ssandbox::exceptions::error_msg(fmt::format("Syscall '{}' not found", x), __FUNCTION__));

        this->_syscall_limit_table.push_back(seccomp_syscall_resolve_name(x.c_str()));
    }
}