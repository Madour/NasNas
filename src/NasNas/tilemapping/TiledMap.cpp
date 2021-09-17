/**
* Created by Modar Nasser on 09/07/2020.
**/

#include "NasNas/core/data/Config.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"
#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/ObjectLayer.hpp"
#include "NasNas/tilemapping/ImageLayer.hpp"
#include "NasNas/tilemapping/GroupLayer.hpp"

#ifdef __ANDROID__
#include "NasNas/core/android/Activity.hpp"
#endif

using namespace ns;
using namespace ns::tm;

TiledMap::TiledMap() = default;

auto TiledMap::loadFromFile(const std::string& file_name) -> bool {
    pugi::xml_document xml;
    pugi::xml_parse_result result;

#ifndef __ANDROID__
    result = xml.load_file(file_name.c_str());
#else
    auto* asset = AAssetManager_open(android::getActivity()->assetManager, file_name.c_str(), AASSET_MODE_BUFFER);
    const auto* filecontent = static_cast<const char*>(AAsset_getBuffer(asset));
    result = xml.load_string(filecontent);
#endif
    if (!result) {
        std::cout << "Error parsing TMX file «" << file_name << "» : " << result.description() << std::endl;
        return false;
    }
    m_file_name = ns::utils::path::getFilename(file_name);
    m_file_relative_path = ns::utils::path::getPath(file_name);
    load(xml);
    return true;
}

auto TiledMap::loadFromString(const std::string& data) -> bool {
    pugi::xml_document xml;
    pugi::xml_parse_result result;
    result = xml.load_string(data.c_str());
    if (!result) {
        std::cout << "Error parsing TMX data : " << result.description() << std::endl;
        return false;
    }
    m_file_name = "";
    m_file_relative_path = "";
    load(xml);
    return true;
}

auto TiledMap::getTMXFilePath() const -> const std::string& {
    return m_file_relative_path;
}

void TiledMap::load(const pugi::xml_document& xml) {
    m_xmlnode_map = xml.child("map");
    m_gridsize.x = m_xmlnode_map.attribute("width").as_uint();
    m_gridsize.y = m_xmlnode_map.attribute("height").as_uint();
    m_tilesize.x = m_xmlnode_map.attribute("tilewidth").as_uint();
    m_tilesize.y = m_xmlnode_map.attribute("tileheight").as_uint();
    m_size.x = static_cast<float>(m_gridsize.x * m_tilesize.x);
    m_size.y = static_cast<float>(m_gridsize.y * m_tilesize.y);

    parseProperties(m_xmlnode_map.child("properties"));

    // parse tilesets
    m_tilesets.reserve(std::distance(m_xmlnode_map.children("tileset").begin(), m_xmlnode_map.children("tileset").end()));
    m_tilesets_data.reserve(m_tilesets.capacity());
    for (const auto& xmlnode_tileset : m_xmlnode_map.children("tileset")) {
        unsigned int firstgid = xmlnode_tileset.attribute("firstgid").as_uint();
        // external tileset
        if (xmlnode_tileset.attribute("source")){
            const auto& tsx_tileset = TsxTilesetsManager::get(m_file_relative_path + xmlnode_tileset.attribute("source").as_string());
            m_tilesets.emplace_back(tsx_tileset, firstgid);
        }
        // embedded tileset
        else {
            m_tilesets_data.emplace_back(xmlnode_tileset, m_file_relative_path);
            m_tilesets.emplace_back(m_tilesets_data.back(), firstgid);
        }
    }

    parseLayers(m_xmlnode_map, this);
}

auto TiledMap::getSize() const -> const sf::Vector2f& {
    return m_size;
}

auto TiledMap::getGridSize() const -> const sf::Vector2u& {
    return m_gridsize;
}

auto TiledMap::getTileSize() const -> const sf::Vector2u& {
    return m_tilesize;
}

auto TiledMap::allTilesets() const -> const std::vector<Tileset>& {
    return m_tilesets;
}

auto TiledMap::getTileTileset(unsigned int gid) const -> const Tileset& {
    for (const auto& tileset : m_tilesets) {
        if (tileset.firstgid <= gid && gid < tileset.firstgid + tileset.data.tilecount)
            return tileset;
    }
    std::cout << "Error (TiledMap::getTileTileset) : Tile gid " << gid << " not found in any tileset" << std::endl;
    exit(-1);
}

void TiledMap::setCamera(const Camera& cam) {
    m_camera = &cam;
}

void TiledMap::update() {
    LayersContainer::update(m_camera);
}
