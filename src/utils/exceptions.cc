#include "ssandbox/utils/exceptions.h"
#include <cerrno>
#include <cstring>
#include <fmt/core.h>

std::string ssandbox::exceptions::error_msg(std::string message, std::string function) {
    return fmt::format("[Segment Sandbox - {}] {}", function, message);
}

ssandbox::exceptions::syscall_error::syscall_error(int errorno, const std::string &message, const std::string &function) {
    this->_message = ssandbox::exceptions::error_msg(fmt::format("{}: [{}] {}", message, errorno, strerror(errorno)), function);
}

ssandbox::exceptions::syscall_error::~syscall_error() {}

const char *ssandbox::exceptions::syscall_error::what() const throw() {
    return this->_message.c_str();
}