#include "ssandbox/utils/exceptions.h"
#include <cerrno>
#include <cstring>
#include <fmt/core.h>

std::string ssandbox::exceptions::getSSErrorMsg(std::string message, std::string function) {
    return fmt::format("[Segment Sandbox - {}] {}", function, message);
}

ssandbox::exceptions::syscall_error::syscall_error(int errorno, std::string message, std::string function) {
    this->_message = ssandbox::exceptions::getSSErrorMsg(fmt::format("{}: [{}] {}", message, errorno, strerror(errorno)), function);
}

ssandbox::exceptions::syscall_error::~syscall_error() {}

const char *ssandbox::exceptions::syscall_error::what() const throw() {
    return this->_message.c_str();
}