/**
 * -*- C++ -*- Part of the Segment Sandbox Project
 * cgroup.h
 *
 * This file is about operating cgroup.
 * 
 */

#ifndef SSANDBOX_CGROUP_H
#define SSANDBOX_CGROUP_H

#include <filesystem>
#include <string>

namespace ssandbox {

const std::filesystem::path cgroup_base("/sys/fs/cgroup/");

class CgroupUnit {
public:
    CgroupUnit(std::string subsys_type, std::string unit_name);
    ~CgroupUnit();

    void write(std::string file, std::string value);
    std::string get(std::string file);
    void remove();

private:
    std::string _subsys_type;
    std::string _unit_name;
    std::filesystem::path _unit_path;
};

class CgroupSubsystem {
public:
    CgroupSubsystem();
    CgroupSubsystem(std::string subsys_type);
    ~CgroupSubsystem();

    void set(std::string subsys_type);
    CgroupUnit* create(std::string unit_name);

private:
    std::string _subsys_type;
};

}; // namespace ssandbox

#endif