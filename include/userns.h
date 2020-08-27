/**
 * -*- C++ -*- Part of the Segment Sandbox Project
 * 
 * unserns.h
 * User namespace supporter of segment-sandbox.
 * 
 * class:
 * UserNamespaceMgr
 * 
 * See the define of these functions in ../src/userns.cc
 */

#ifndef SSANDBOX_USERNS_H
#define SSANDBOX_USERNS_H

#include <string>
#include <unistd.h>

namespace ssandbox {

class UserNamespaceMgr {
public:
    void setUIDMap(pid_t pid, int inside_id, int outside_id, int length);
    void setGIDMap(pid_t pid, int inside_id, int outside_id, int length);
    static UserNamespaceMgr* getInstance();

private:
    UserNamespaceMgr();
    ~UserNamespaceMgr();

    static UserNamespaceMgr* _instance;

    void setMap(std::string file, int inside_id, int outside_id, int length);
};

} // namespace ssandbox

#endif // SSANDBOX_USRNS_H