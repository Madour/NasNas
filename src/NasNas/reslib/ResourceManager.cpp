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

auto ResourceManager::load(const std::string& assets_directory_name) -> bool {
    try {
        m_data = new Dir(assets_directory_name);
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

auto ResourceManager::get() -> Dir& {
    if (!m_ready) {
        std::cout << "Error : ResourceManager is not initialized. Call Res::load(<dir_name>) first." << std::endl;
        exit(-1);
    }
    return *m_data;
}

void ResourceManager::printTree() {
    if (!m_ready) {
        std::cout << "Error : ResourceManager is not initialized. Call Res::load(<dir_name>) first." << std::endl;
        exit(-1);
    }
    std::cout << std::endl << m_data->getName() << std::endl;
    m_data->print_tree();
}
