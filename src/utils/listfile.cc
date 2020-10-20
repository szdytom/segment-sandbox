#include "ssandbox/utils/listfile.h"
#include <cerrno>
#include <cstdio>
#include <fmt/core.h>
#include "ssandbox/utils/exceptions.h"

ssandbox::io::list_file_reader::list_file_reader(const std::string& filename) {
    this->filename = filename;
}

ssandbox::io::list_file_reader::~list_file_reader() {}

std::vector<std::string> ssandbox::io::list_file_reader::read() {
    std::vector<std::string> res;

    std::FILE* file = std::fopen(this->filename.c_str(), "r");
    if (file == nullptr)
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot open list file: '{}'", this->filename),
                                                  __FUNCTION__);

    char* line = new char[4096];
    while (~std::fscanf(file, " %4095[^\n\r]", line)) {
        char* line_begin = line;
        while (*line_begin != '\0' && (*line_begin == ' ' || *line_begin == '\t'))
            line_begin += 1;

        for (int i = 0; line_begin[i] != '\0'; ++i) {
            if (line_begin[i] == '#') {
                line_begin[i] = '\0';
                break;
            }
        }

        int last_char_index = -1;
        for (int i = 0; line_begin[i] != '\0'; ++i) {
            if (line_begin[i] != ' ' && line_begin[i] != '\t')
                last_char_index = i;
        }
        line_begin[last_char_index + 1] = '\0';

        std::string this_line(line_begin);
        if (this_line.empty())
            continue;

        res.push_back(line_begin);
    }

    delete[] line;
    std::fclose(file);
    return res;
}