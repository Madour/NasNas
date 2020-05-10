/**
* Created by Modar Nasser on 23/04/2020.
**/

#include "NasNas/reslib/ResourceManager.hpp"

using namespace ns;

ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() {
    delete(data);
}

bool ResourceManager::ready = false;
Dir* ResourceManager::data = nullptr;


auto ResourceManager::load(const std::string& assets_directory_name) -> bool {
    try {
        data = new Dir(assets_directory_name);
        data->load(std::filesystem::current_path().append(assets_directory_name));
        ready = true;
        return true;
    }
    catch (std::exception& e) {
        std::cout << "Error : ResourceLoading failed. The directory " << assets_directory_name << " was not found." << std::endl;
        return false;
    }
}

void ResourceManager::dispose() {
    if(ready)
        delete(data);
}

auto ResourceManager::get() -> Dir& {
    if (!ready) {
        std::cout << "Error : ResourceManager is not initialized. Call Res::load(<dir_name>) first." << std::endl;
        std::exit(-1);
    }
    return *data;
}

void ResourceManager::printTree() {
    if (!ready) {
        std::cout << "Error : ResourceManager is not initialized. Call Res::load(<dir_name>) first." << std::endl;
        std::exit(-1);
    }
    std::cout << std::endl << data->getName() << std::endl;
    data->print_tree();
}