#include "ssandbox/global_config.h"
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <string>
#include <fmt/core.h>
#include "ssandbox/utils/exceptions.h"

ssandbox::global_config* ssandbox::global_config::_instance = nullptr;

ssandbox::global_config::global_config() {}
ssandbox::global_config::~global_config() {}

ssandbox::global_config* ssandbox::global_config::get_instance() {
    if (ssandbox::global_config::_instance == nullptr)
        ssandbox::global_config::_instance = new ssandbox::global_config;

    return ssandbox::global_config::_instance;
}

void* ssandbox::global_config::get_field(std::string key) {
    if (this->_storage.find(key) == this->_storage.end())
        return nullptr;

    return this->_storage.at(key);
}

void ssandbox::global_config::set_feild(std::string key, void* val) {
    if (this->_storage.find(key) != this->_storage.end())
        this->_storage.at(key) = val;
    else
        this->_storage.insert(std::make_pair(key, val));
}

void ssandbox::global_config::remove_feild(std::string key) {
    if (this->_storage.find(key) == this->_storage.end())
        throw std::logic_error(ssandbox::exceptions::error_msg(fmt::format("Cannot remove feild '{}': feild not found."), __FUNCTION__));

    this->_storage.erase(key);
}