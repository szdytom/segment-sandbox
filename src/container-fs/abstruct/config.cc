#include <filesystem>
#include <fmt/core.h>
#include "ssandbox/containerfs.h"

void ssandbox::AbstructContainerFS::enableTmp(bool enable) {
    this->_mount_tmp = enable;
}

void ssandbox::AbstructContainerFS::enableProc(bool enable) {
    this->_mount_proc = enable;
}

void ssandbox::AbstructContainerFS::setUID(const std::string& uid) {
    this->uid = uid;
}

void ssandbox::AbstructContainerFS::setWorkspace(const std::filesystem::path& workspace_path) {
    if (!std::filesystem::exists(workspace_path))
        std::filesystem::create_directories(workspace_path);

    this->workspace = workspace_path;
}

void ssandbox::AbstructContainerFS::setImage(const std::filesystem::path& image_path) {
    if (!std::filesystem::exists(image_path))
        throw std::runtime_error(fmt::format("[Segment Sandobx - {}] Image Directory '{}' not found.", __FUNCTION__, image_path.string()));

    this->image_path = image_path;
}

std::filesystem::path ssandbox::AbstructContainerFS::getFSPath(const std::filesystem::path& name) {
    std::filesystem::path res = this->workspace / this->uid / name;
    if (!std::filesystem::exists(res))
        std::filesystem::create_directories(res);

    return res;
}
