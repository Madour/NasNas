/**
* Created by Modar Nasser on 09/07/2020.
**/

#include "NasNas/data/Config.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"
#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/ObjectLayer.hpp"

using namespace ns;
using namespace ns::tm;

TiledMap::TiledMap() = default;

auto TiledMap::loadFromFile(const std::string& file_name) -> bool {
    pugi::xml_document xml;
    auto result = xml.load_file(file_name.c_str());
    if (!result) {
        std::cout << "Error parsing TMX file «" << file_name << "» : " << result.description() << std::endl;
        return false;
    }
    m_file_name = std::filesystem::path(file_name).filename().string();
    m_file_relative_path = std::filesystem::path(file_name).remove_filename();
    load(xml);
    return true;
}

auto TiledMap::loadFromString(const std::string& data) -> bool {
    pugi::xml_document xml;
    auto result = xml.load_string(data.c_str());
    if (!result) {
        std::cout << "Error parsing TMX data : " << result.description() << std::endl;
        return false;
    }
    m_file_name = "";
    m_file_relative_path = Config::base_path;
    load(xml);
    return true;
}

void TiledMap::load(const pugi::xml_document& xml) {
    m_xmlnode_map = xml.child("map");
    m_size.x = m_xmlnode_map.attribute("width").as_uint();
    m_size.y = m_xmlnode_map.attribute("height").as_uint();
    m_tilesize.x = m_xmlnode_map.attribute("tilewidth").as_uint();
    m_tilesize.y = m_xmlnode_map.attribute("tileheight").as_uint();

    parseProperties(m_xmlnode_map.child("properties"));

    // parsing tilesets
    for (const auto& xmlnode_tileset : m_xmlnode_map.children("tileset")) {
        unsigned int firstgid = xmlnode_tileset.attribute("firstgid").as_uint();
        // external tileset
        if (xmlnode_tileset.attribute("source")){
            const auto& tsx_tileset = SharedTilesetManager::get((m_file_relative_path / xmlnode_tileset.attribute("source").as_string()).string());
            m_tilesets.push_back(std::make_unique<Tileset>(tsx_tileset, firstgid));
        }
        // embedded tileset
        else
            m_tilesets.push_back(std::make_unique<Tileset>(xmlnode_tileset, m_file_relative_path.string()));
    }

    // parsing layers
    for (const auto& xmlnode_layer : m_xmlnode_map.children("layer")) {
        auto new_layer = std::make_shared<TileLayer>(xmlnode_layer, this);
        m_layers[{new_layer->getId(), new_layer->getName()}] = new_layer;
    }
    // parsing object layers
    for (const auto& xmlnode_layer : m_xmlnode_map.children("objectgroup")) {
        auto new_layer = std::make_shared<ObjectLayer>(xmlnode_layer, this);
        m_objectlayers[{new_layer->getId(), new_layer->getName()}] = new_layer;
    }
}

auto TiledMap::getSize() -> const sf::Vector2u& {
    return m_size;
}

auto TiledMap::getTileSize() -> const sf::Vector2u& {
    return m_tilesize;
}

auto TiledMap::getTileTileset(unsigned int gid) -> const std::unique_ptr<Tileset>& {
    int return_index = 0; int i = 0;
    for (const auto& tileset : m_tilesets) {
        if (gid >= tileset->firstgid) {
            return_index = i;
            i++;
        }
        else
            continue;
    }
    return m_tilesets[return_index];
}

auto TiledMap::allTilesets() -> const std::vector<std::unique_ptr<Tileset>>& {
    return m_tilesets;
}

auto TiledMap::getTileLayer(const std::string& name) -> const std::shared_ptr<TileLayer>& {
    for (const auto& [key, layer_ptr] : m_layers) {
        if (key.second == name) {
            return m_layers[key];
        }
    }
    std::cout << "TiledMap «" << m_file_name << "» has not TileLayer named «" << name << "»." << std::endl;
    exit(-1);
}

auto TiledMap::getObjectLayer(const std::string& name) -> const std::shared_ptr<ObjectLayer>& {
    for (const auto& [key, layer_ptr] : m_objectlayers) {
        if (key.second == name) {
            return m_objectlayers[key];
        }
    }
    std::cout << "TiledMap «" << m_file_name << "» has not ObjectLayer named «" << name << "»." << std::endl;
    exit(-1);
}
