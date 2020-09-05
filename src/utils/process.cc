#include "ssandbox/utils/process.h"
#include <filesystem>

bool ssandbox::utils::process::checkProcessAlive(pid_t pid) {
    std::filesystem::path process_proc("/proc");
    process_proc /= std::to_string(pid);

    if (std::filesystem::exists(process_proc))
        return true;
    else
        return false;
}