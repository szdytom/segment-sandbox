// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_CGROUP_H
#define SSANDBOX_CGROUP_H

#include <filesystem>
#include <string>

namespace ssandbox {

const std::filesystem::path cgroup_base("/sys/fs/cgroup/");

class cgroup_unit {
public:
    cgroup_unit(const std::string& subsys_type, const std::string& unit_name);
    ~cgroup_unit();

    void write(const std::string& file, const std::string& value) const;
    std::string get(const std::string& file) const;
    void remove() const;

    std::string get_subsys_type() const;

private:
    std::string _subsys_type;
    std::string _unit_name;
    std::filesystem::path _unit_path;
};

class cgroup_subsystem {
public:
    cgroup_subsystem();
    explicit cgroup_subsystem(std::string subsys_type);
    ~cgroup_subsystem();

    void set(std::string subsys_type);
    cgroup_unit* create(std::string unit_name);

private:
    std::string _subsys_type;
};

}; // namespace ssandbox

#endif