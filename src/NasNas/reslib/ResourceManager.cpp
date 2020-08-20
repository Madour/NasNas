/**
* Created by Modar Nasser on 23/04/2020.
**/


#include "NasNas/reslib/ResourceManager.hpp"
#include "NasNas/data/Arial.hpp"

using namespace ns;

ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;

bool ResourceManager::m_ready = false;
Dir* ResourceManager::m_data = nullptr;
std::string ResourceManager::m_root_dir;

auto ResourceManager::load(const std::string& assets_directory_name) -> bool {
    try {
        m_data = new Dir(assets_directory_name, nullptr);
        m_root_dir = assets_directory_name;
        m_data->load(std::filesystem::current_path().append(assets_directory_name));
        m_ready = true;
        return true;
    }
    catch (std::exception&) {
        std::cout << "Error : ResourceLoading failed. The directory " << assets_directory_name << " was not found." << std::endl;
        return false;
    }
}

void ResourceManager::dispose() {
    if(m_ready)
        delete(m_data);
}

void ResourceManager::checkReady() {
    if (m_ready) return;
    std::cout << "Error : ResourceManager is not initialized. Call ns::Res::load(<dir_name>) first." << std::endl;
    exit(-1);
}

auto ResourceManager::get() -> Dir& {
    checkReady();
    return *m_data;
}

auto ResourceManager::getName() -> const std::string & {
    return m_root_dir;
}

auto ResourceManager::getTexture(const std::string& texture_path) -> sf::Texture& {
    checkReady();

    std::string path = texture_path;
    auto first_slash_idx = texture_path.find_first_of('/');
    //checking if only file name
    if (first_slash_idx == std::string::npos)
        return m_data->getTexture(texture_path);
    // checking if absolute path and make it relative to Res root dir
    else if (texture_path.substr(0, first_slash_idx) == m_root_dir)
        path = texture_path.substr(first_slash_idx+1, texture_path.size());

    Dir* current_dir = m_data;
    int separator_index = path.find_first_of('/'), temp = 0;

    // resolving path
    while(separator_index != std::string::npos) {
        auto dir_name = path.substr(temp, separator_index);
        path = path.substr(separator_index+1, path.size());
        current_dir = &current_dir->in(dir_name);
        separator_index = path.find_first_of('/');
    }
    return current_dir->getTexture(path);
}

auto ResourceManager::getFont(const std::string& font_path) -> sf::Font& {
    checkReady();

    std::string path = font_path;
    auto first_slash_idx = font_path.find_first_of('/');
    //checking if only file name
    if (first_slash_idx == std::string::npos)
        return m_data->getFont(font_path);
        // checking if absolute path and make it relative to Res root dir
    else if (font_path.substr(0, first_slash_idx) == m_root_dir)
        path = font_path.substr(first_slash_idx+1, font_path.size());

    int separator_index = path.find_first_of('/'), temp = 0;
    Dir* current_dir = m_data;

    // resolving path
    while(separator_index != std::string::npos) {
        auto dir_name = path.substr(temp, separator_index);
        path = path.substr(separator_index+1, path.size());
        current_dir = &m_data->in(dir_name);
        separator_index = path.find_first_of('/');
    }
    return current_dir->getFont(path);
}

void ResourceManager::printTree() {
    checkReady();
    std::cout << std::endl << m_data->getName() << std::endl;
    m_data->print_tree();
}
