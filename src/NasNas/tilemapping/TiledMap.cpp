/**
* Created by Modar Nasser on 09/07/2020.
**/


#include "NasNas/tilemapping/TiledMap.hpp"
#include "NasNas/tilemapping/TileLayer.hpp"

using namespace ns;
using namespace ns::tm;

TiledMap::TiledMap() = default;

auto TiledMap::loadFromFile(const std::string& file_name) -> bool {
    pugi::xml_document xml;
    auto result = xml.load_file(file_name.c_str());
    if (!result) {
        std::cout << "Error parsing XML file «" << file_name << "» : " << result.description() << std::endl;
        return false;
    }
    m_file_name = std::filesystem::path(file_name).filename().string();
    m_file_path = std::filesystem::current_path().append(file_name).remove_filename();
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
    m_size.x = m_xml_node.attribute("width").as_uint();
    m_size.y = m_xml_node.attribute("height").as_uint();
    m_tilesize.x = m_xml_node.attribute("tilewidth").as_uint();
    m_tilesize.y = m_xml_node.attribute("tileheight").as_uint();

    // parsing properties
    for (const auto& xml_prop : m_xml_node.child("properties").children()) {
        addProperty(xml_prop);
    }
    // parsing tilesets
    for (const auto& xml_tileset : m_xml_node.children("tileset")) {
        m_tilesets[xml_tileset.attribute("firstgid").as_uint()] = std::make_shared<Tileset>(xml_tileset, m_file_path);
    }
    // parsing layers
    for (const auto& xml_layer : m_xml_node.children("layer")) {
        auto new_layer = std::make_shared<TileLayer>(xml_layer, this);
        m_layers[{new_layer->getId(), new_layer->getName()}] = new_layer;
    }
}

auto TiledMap::getSize() -> const sf::Vector2u& {
    return m_size;
}

auto TiledMap::getTileSize() -> const sf::Vector2u& {
    return m_tilesize;
}

auto TiledMap::getTileTileset(unsigned int gid) -> std::pair<int, const Tileset*> {
    Tileset* current_tileset;
    int first_gid;
    for (const auto& [firstgid, tileset_shared_ptr] : m_tilesets) {
        if (gid >= firstgid) {
            current_tileset = tileset_shared_ptr.get();
            first_gid = firstgid;
        }
        else
            continue;
    }
    return std::make_pair<>(first_gid, current_tileset);
}

auto TiledMap::allTilesets() -> std::map<unsigned int, std::shared_ptr<Tileset>> & {
    return m_tilesets;
}

auto TiledMap::getTileLayer(const std::string& name) -> std::shared_ptr<TileLayer>& {
    for (auto& [key, layer_ptr] : m_layers) {
        if (key.second == name) {
            return layer_ptr;
        }
    }
    std::cout << "TiledMap «" << m_file_name << "» had not TileLayer names «" << name << "»." << std::endl;
    exit(-1);
}


