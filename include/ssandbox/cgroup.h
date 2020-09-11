// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_CGROUP_H
#define SSANDBOX_CGROUP_H

#include <filesystem>
#include <string>

namespace ssandbox {

const std::filesystem::path cgroup_base("/sys/fs/cgroup/");

class cgroup_unit {
public:
    cgroup_unit(std::string subsys_type, std::string unit_name);
    ~cgroup_unit();

    void write(std::string file, std::string value);
    std::string get(std::string file);
    void remove();

private:
    std::string _subsys_type;
    std::string _unit_name;
    std::filesystem::path _unit_path;
};

class cgroup_subsystem {
public:
    cgroup_subsystem();
    cgroup_subsystem(std::string subsys_type);
    ~cgroup_subsystem();

    void set(std::string subsys_type);
    cgroup_unit* create(std::string unit_name);

private:
    std::string _subsys_type;
};

}; // namespace ssandbox

#endif