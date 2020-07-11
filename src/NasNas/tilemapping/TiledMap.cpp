/**
* Created by Modar Nasser on 09/07/2020.
**/


#include "NasNas/tilemapping/TiledMap.hpp"
#include "NasNas/tilemapping/TileLayer.hpp"

using namespace ns;
using namespace ns::tm;

TiledMap::TiledMap() = default;

auto TiledMap::loadFromFile(const std::string &file_name) -> bool {
    pugi::xml_document xml;
    auto result = xml.load_file(file_name.c_str());
    if (!result) {
        std::cout << "Error parsing XML file «" << file_name << "» : " << result.description() << std::endl;
        return false;
    }
    load(xml);
    return true;
}

auto TiledMap::loadFromString(const std::string& data) -> bool {
    pugi::xml_document xml;
    auto result = xml.load_string(data.c_str());
    if (!result) {
        std::cout << "Error parsing XML data : " << result.description() << std::endl;
        return false;
    }
    load(xml);
    return true;
}


void TiledMap::load(const pugi::xml_document& xml) {
    m_xml_node = xml.child("map");
    m_width = m_xml_node.attribute("width").as_int();
    m_height = m_xml_node.child("map").attribute("height").as_int();
    m_tilewidth = m_xml_node.child("map").attribute("tilewidth").as_int();
    m_tileheight = m_xml_node.child("map").attribute("tileheight").as_int();

    // parsing properties
    for (const auto& xml_prop : m_xml_node.child("properties").children()) {
        addProperty(xml_prop);
    }
    // parsing layers
    for (const auto& xml_layer : m_xml_node.children("layer")) {
        auto new_layer = std::make_shared<TileLayer>(xml_layer, this);
        m_layers[{new_layer->getId(), new_layer->getName()}] = new_layer;
    }
}
