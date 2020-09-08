#include "ssandbox/utils/process.h"
#include <filesystem>
#include <fmt/core.h>
#include <limits.h>

bool ssandbox::utils::process::checkProcessAlive(pid_t pid) {
    std::filesystem::path process_proc("/proc");
    process_proc /= std::to_string(pid);

    if (!std::filesystem::exists(process_proc))
        return false; // process does not exsit

    std::string statfilepath = fmt::format("/proc/{}/stat", pid);
    std::FILE* statfile = std::fopen(statfilepath.c_str(), "r");
    int readpid;
    char *name = new char[PATH_MAX + 1];
    char *stat = new char[64];
    fscanf(statfile, "%d %s %s", &readpid, name, stat);

    bool ret = true;
    for (int i = 0; stat[i] != '\0'; ++i) {
        if (stat[i] == 'Z') ret = false; // Process has dead
    }

    delete[] name;
    delete[] stat;
    return ret;
}