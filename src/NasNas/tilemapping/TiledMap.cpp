/**
* Created by Modar Nasser on 09/07/2020.
**/

#include "NasNas/tilemapping/TiledMap.hpp"
#include "NasNas/core/Logger.hpp"

using namespace ns;

TiledMap::TiledMap() = default;

void TiledMap::load() {
    m_width = std::stoi(std::string(m_xml.child("map").attribute("width").value()));
    m_height = std::stoi(std::string(m_xml.child("map").attribute("height").value()));
    m_tilewidth = std::stoi(std::string(m_xml.child("map").attribute("tilewidth").value()));
    m_tileheight = std::stoi(std::string(m_xml.child("map").attribute("tileheight").value()));
}

auto TiledMap::loadFromFile(const std::string &file_name) -> bool {
    auto result = m_xml.load_file(file_name.c_str());
    if (!result) {
        std::cout << "Error parsing XML file «" << file_name << "» : " << result.description() << std::endl;
        return false;
    }
    load();
    return true;
}

auto TiledMap::loadFromString(const std::string& data) -> bool {
    auto result = m_xml.load_string(data.c_str());
    if (!result) {
        std::cout << "Error parsing XML data : " << result.description() << std::endl;
        return false;
    }
    load();
    return true;
}