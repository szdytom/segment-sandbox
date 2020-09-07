#include "ssandbox/utils/exceptions.h"
#include <cerrno>
#include <cstring>
#include <fmt/format.h>

ssandbox::utils::exceptions::syscall_error::syscall_error(int errorno, std::string message, std::string function) {
    this->_message = fmt::format("[Segment Sandbox - {}] {}: [{}] {}", function, message, errorno, strerror(errorno));
}

ssandbox::utils::exceptions::syscall_error::~syscall_error() {}

const char *ssandbox::utils::exceptions::syscall_error::what() const throw() {
    return this->_message.c_str();
}