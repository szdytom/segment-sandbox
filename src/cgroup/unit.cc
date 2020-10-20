#include <cerrno>
#include <cstdio>
#include <filesystem>
#include <fmt/core.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ssandbox/cgroup.h"
#include "ssandbox/utils/exceptions.h"

ssandbox::cgroup_unit::cgroup_unit(const std::string& subsys_type, const std::string& unit_name) {
    this->_subsys_type = subsys_type;
    this->_unit_name = unit_name;

    this->_unit_path = cgroup_base;
    this->_unit_path /= subsys_type;
    this->_unit_path /= unit_name;

    if (!std::filesystem::exists(this->_unit_path)) {
        std::filesystem::create_directory(this->_unit_path);
    }
}

ssandbox::cgroup_unit::~cgroup_unit() {}

void ssandbox::cgroup_unit::write(const std::string& file, const std::string& value) const {
    std::filesystem::path file_path(this->_unit_path);
    file_path /= file;

    FILE* f = std::fopen(file_path.c_str(), "w");

    if (f == nullptr)
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot open cgroup file '{}'", file),
                                                  __FUNCTION__);

    std::fprintf(f, "%s", value.c_str());
    std::fclose(f);
}

std::string ssandbox::cgroup_unit::get(const std::string& file) const {
    std::filesystem::path file_path(this->_unit_path);
    file_path /= file;

    FILE* f = std::fopen(file_path.c_str(), "r");

    if (f == nullptr)
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot open file cgroup '{}'", file),
                                                  __FUNCTION__);

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

void ssandbox::cgroup_unit::remove() const {
    std::filesystem::remove(this->_unit_path);
}

std::string ssandbox::cgroup_unit::get_subsys_type() const {
    return this->_subsys_type;
}