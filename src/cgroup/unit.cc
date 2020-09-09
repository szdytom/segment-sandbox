#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/utils/exceptions.h"

ssandbox::CgroupUnit::CgroupUnit(std::string subsys_type, std::string unit_name) {
    this->_subsys_type = subsys_type;
    this->_unit_name = unit_name;

    this->_unit_path = cgroup_base;
    this->_unit_path /= subsys_type;
    this->_unit_path /= unit_name;

    if (!std::filesystem::exists(this->_unit_path)) {
        std::filesystem::create_directory(this->_unit_path);
    }
}

ssandbox::CgroupUnit::~CgroupUnit() {}

void ssandbox::CgroupUnit::write(std::string file, std::string value) {
    std::filesystem::path file_path(this->_unit_path);
    file_path /= file;

    FILE* f = std::fopen(file_path.c_str(), "w");

    if (f == nullptr)
        throw ssandbox::utils::exceptions::syscall_error(errno, fmt::format("Cannot open cgroup file '{}'"), __FUNCTION__);

    fmt::print(f, "{}", value);
    fclose(f);
}

std::string ssandbox::CgroupUnit::get(std::string file) {
    std::filesystem::path file_path(this->_unit_path);
    file_path /= file;

    FILE* f = std::fopen(file_path.c_str(), "r");

    if (f == nullptr)
        throw std::runtime_error(fmt::format("[Segment Sandbox -{}] Cannot open file cgroup '{}': [{}] {}", __FUNCTION__, file_path.string(), errno, strerror(errno)));

    /* Scan all content inside */
    std::fseek(f, 0, SEEK_END);        /* jump to end */
    int length = std::ftell(f);        /* calc file length */
    char* data = new char[length + 1]; /* new need space(+1 for '\0') */
    std::rewind(f);                    /* jump back to begin */

    length = std::fread(data, 1, length, f);
    data[length] = '\0';
    std::string result(data);

    delete[] data;
    return result;
}

void ssandbox::CgroupUnit::remove() {
    std::filesystem::remove(this->_unit_path);
}