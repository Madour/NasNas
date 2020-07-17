/**
* Created by Modar Nasser on 14/07/2020.
**/


#include <filesystem>
#include "NasNas/tilemapping/Tileset.hpp"

using namespace ns;
using namespace ns::tm;

std::unordered_map<std::string, std::shared_ptr<TsxTileset>> TilesetManager::m_tsx_tilesets;

TsxTileset::TsxTileset(const pugi::xml_node& xml_node, const std::string& path) :
name(xml_node.attribute("name").as_string()),
tilewidth(xml_node.attribute("tilewidth").as_uint()),
tileheight(xml_node.attribute("tileheight").as_uint()),
tilecount(xml_node.attribute("tilecount").as_uint()),
columns(xml_node.attribute("columns").as_uint()) {
    m_image_source = xml_node.child("image").attribute("source").as_string();

    m_texture = std::make_shared<sf::Texture>();
    m_texture->loadFromFile(path + m_image_source);

    // parsing tileset properties
    for (const auto& xml_prop : xml_node.child("properties").children()) {
        addProperty(xml_prop);
    }
    // parsing tileset tiles properties
    for (const auto& xml_tile : xml_node.children("tile")) {
        auto tile_id =  xml_tile.attribute("id").as_uint();
        for (const auto& xml_tile_prop : xml_tile.child("properties").children())
            m_tile_properties[tile_id].addProperty(xml_tile);
    }
}

auto TsxTileset::getTexture() const -> const sf::Texture & {
    return *m_texture;
}

Tileset::Tileset(const pugi::xml_node& xml_node, const std::string& base_path) :
TsxTileset(xml_node, base_path),
firstgid(xml_node.attribute("firstgid").as_uint())
{}

Tileset::Tileset(const TsxTileset& tsx_tileset, unsigned int first_gid) :
TsxTileset(tsx_tileset),
firstgid(first_gid)
{}

auto TilesetManager::get(const std::string &tsx_file_name) -> const TsxTileset & {
    if (m_tsx_tilesets.count(tsx_file_name))
        return *m_tsx_tilesets[tsx_file_name].get();
    else {
        pugi::xml_document xml;
        auto result = xml.load_file(tsx_file_name.c_str());
        if (!result) {
            std::cout << "Error parsing TSX file «" << tsx_file_name << "» : " << result.description() << std::endl;
            std::exit(-1);
        }
        m_tsx_tilesets[tsx_file_name] =  std::make_shared<TsxTileset>(xml.child("tileset"), std::filesystem::path(tsx_file_name).remove_filename());
        return *m_tsx_tilesets[tsx_file_name].get();
    }
}