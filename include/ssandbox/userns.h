// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_USERNS_H
#define SSANDBOX_USERNS_H

#include <string>
#include <sched.h>

namespace ssandbox {

class user_namespace_manager {
public:
    void set_uid_map(pid_t pid, int inside_id, int outside_id, int length);
    void set_gid_map(pid_t pid, int inside_id, int outside_id, int length);
    static user_namespace_manager* get_instance();

private:
    user_namespace_manager();
    ~user_namespace_manager();

    static user_namespace_manager* _instance;

    void _set_map(std::string file, int inside_id, int outside_id, int length);
};

} // namespace ssandbox

#endif // SSANDBOX_USRNS_H