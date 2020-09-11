#include <filesystem>
#include <fmt/core.h>
#include "ssandbox/containerfs.h"

void ssandbox::AbstructContainerFS::enable_tmp(bool enable) {
    this->_mount_tmp_flag = enable;
}

void ssandbox::AbstructContainerFS::enable_proc(bool enable) {
    this->_mount_proc_flag = enable;
}

void ssandbox::AbstructContainerFS::set_uid(const std::string& uid) {
    this->uid = uid;
}

void ssandbox::AbstructContainerFS::set_workspace(const std::filesystem::path& workspace_path) {
    if (!std::filesystem::exists(workspace_path))
        std::filesystem::create_directories(workspace_path);

    this->workspace = workspace_path;
}

void ssandbox::AbstructContainerFS::set_image(const std::filesystem::path& image_path) {
    if (!std::filesystem::exists(image_path))
        throw std::runtime_error(fmt::format("[Segment Sandobx - {}] Image Directory '{}' not found.", __FUNCTION__, image_path.string()));

    this->image_path = image_path;
}

std::filesystem::path ssandbox::AbstructContainerFS::get_fs_path(const std::filesystem::path& name) {
    std::filesystem::path res = this->workspace / this->uid / name;
    if (!std::filesystem::exists(res))
        std::filesystem::create_directories(res);

    return res;
}
