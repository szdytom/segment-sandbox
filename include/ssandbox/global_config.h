// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_GLOBAL_CONFIG_H
#define SSANDBOX_GLOBAL_CONFIG_H

#include <map>
#include <string>

namespace ssandbox {

class global_config {
public:
    void* get_field(std::string key);
    void set_feild(std::string key, void* val);
    void remove_feild(std::string key);

    static global_config* get_instance();

private:
    global_config();
    ~global_config();

    static global_config* _instance;
    std::map<std::string, void*> _storage;
};

} // namespace ssandbox

#endif // SSANDBOX_GLOBAL_CONFIG_H