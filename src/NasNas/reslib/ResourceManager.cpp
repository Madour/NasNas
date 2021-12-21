/**
* Created by Modar Nasser on 23/04/2020.
**/


#include <NasNas/reslib/ResourceManager.hpp>

#include <iostream>
#ifndef __ANDROID__
#include <filesystem>
#endif

using namespace ns;

ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;

bool ResourceManager::m_ready = false;
Dir* ResourceManager::m_data = nullptr;
std::string ResourceManager::m_root_dir_name;

auto ResourceManager::load(const std::string& assets_directory_name, bool autoload) -> bool {
    if (m_data != nullptr) {
        delete m_data;
        m_data = nullptr;
    }
    try {
        m_data = new Dir(assets_directory_name, nullptr);
        m_root_dir_name = assets_directory_name;
#ifndef __ANDROID__
        m_data->load(std::filesystem::current_path().append(assets_directory_name).string(), autoload);
#else
        m_data->load(assets_directory_name, autoload);
#endif
        m_ready = true;
        return true;
    }
    catch (std::exception&) {
        std::cerr << "Error : ResourceLoading failed. The directory " << assets_directory_name << " was not found." << std::endl;
        return false;
    }
}

void ResourceManager::dispose() {
    if(m_ready)
        delete(m_data);
}

void ResourceManager::checkReady() {
    if (m_ready) return;
    std::cerr << "Error : ResourceManager is not initialized. Call ns::Res::load(<dir_name>) first." << std::endl;
    exit(-1);
}

auto ResourceManager::in(const std::string& dir_name) -> Dir& {
    checkReady();
    return m_data->in(dir_name);
}

auto ResourceManager::getName() -> const std::string & {
    return m_root_dir_name;
}

auto ResourceManager::getTexture(const std::string& texture_path) -> sf::Texture& {
    checkReady();
    auto [dir, path] = resolvePath(texture_path);
    return dir->getTexture(path);
}

auto ResourceManager::getFont(const std::string& font_path) -> sf::Font& {
    checkReady();
    auto [dir, path] = resolvePath(font_path);
    return dir->getFont(path);
}

auto ResourceManager::resolvePath(const std::string& p) -> std::pair<Dir*, std::string> {
    std::string path = p;
    auto first_slash_idx = p.find_first_of('/');

    //check if only file name
    if (first_slash_idx == std::string::npos)
        return {m_data, path};
    // check if absolute path and make it relative to Res root dir
    else if (p.substr(0, first_slash_idx) == m_root_dir_name)
        path = p.substr(first_slash_idx+1, p.size());

    Dir* current_dir = m_data;
    std::size_t separator_index = path.find_first_of('/');
    std::size_t temp = 0;

    // resolve path
    while(separator_index != std::string::npos) {
        auto dir_name = path.substr(temp, separator_index);
        path = path.substr(separator_index+1, path.size());
        current_dir = &current_dir->in(dir_name);
        separator_index = path.find_first_of('/');
    }
    return {current_dir, path};
}

void ResourceManager::printTree() {
    checkReady();
    std::cout << '\n' << m_data->getName() << '\n';
    m_data->printTree();
    std::cout << std::endl;
}
