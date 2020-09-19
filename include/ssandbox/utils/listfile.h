// -*- C++ -*- Part of the Segment Sandbox Project

#include <cstdio>
#include <string>
#include <vector>

#ifndef SSANDBOX_UTILS_LISTFILE_H
#define SSANDBOX_UTILS_LISTFILE_H

namespace ssandbox {

namespace io {

class list_file_reader {
public:
    list_file_reader(std::string filename);
    ~list_file_reader();

    std::vector<std::string> read();

private:
    std::string filename;
};

} // namespace io

} // namespace ssandbox

#endif // SSANDBOX_UTILS_LISTFILE_H