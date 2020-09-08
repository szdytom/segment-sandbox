#include <fmt/core.h>
#include "ssandbox/containerfs.h"

void ssandbox::AbstructContainerFS::enableTmp(bool enable) {
    this->_mount_tmp = true;
}

void ssandbox::AbstructContainerFS::enableProc(bool enable) {
    this->_mount_proc = true;
}

void ssandbox::AbstructContainerFS::setUID(const std::string& uid) {
    this->uid = uid;
}

void ssandbox::AbstructContainerFS::setWorkspace(const std::filesystem::path& workspace_path) {
    this->workspace = workspace_path;
}

void ssandbox::AbstructContainerFS::setImage(const std::filesystem::path& image_path) {
    this->image_path = image_path;
}

std::filesystem::path ssandbox::AbstructContainerFS::getFSPath(const std::filesystem::path& name) {
    return this->workspace / name;
}
