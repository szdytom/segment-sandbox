#include "ssandbox/utils/process.h"
#include <cerrno>
#include <climits>
#include <filesystem>
#include <fmt/core.h>
#include "ssandbox/utils/exceptions.h"

bool ssandbox::process::check_process_alive(pid_t pid) {
    std::filesystem::path process_proc("/proc");
    process_proc /= std::to_string(pid);

    if (!std::filesystem::exists(process_proc))
        return false; // process does not exsit

    std::string statfilepath = fmt::format("/proc/{}/stat", pid);
    std::FILE* statfile = std::fopen(statfilepath.c_str(), "r");

    if (statfile == nullptr)
        throw ssandbox::exceptions::syscall_error(errno, fmt::format("Cannot open process file of pid={}", pid),
                                                  __FUNCTION__);

    char* stat = new char[64];
    std::fscanf(statfile, "%*[0-9] (%*[^/()\n\r]) %63s", stat);

    bool ret = true;
    for (int i = 0; stat[i] != '\0'; ++i) {
        if (stat[i] == 'Z')
            ret = false; // Process has dead
    }

    std::fclose(statfile);
    delete[] stat;
    return ret;
}