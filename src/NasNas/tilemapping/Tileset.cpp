/**
* Created by Modar Nasser on 14/07/2020.
**/


#include <filesystem>
#include "NasNas/tilemapping/Tileset.hpp"
#ifdef NS_RESLIB
#include "NasNas/reslib/ResourceManager.hpp"
#endif

using namespace ns;
using namespace ns::tm;

TilesetManager::TilesetManager() = default;

auto TilesetManager::get(const std::string& tsx_file_name) -> const std::shared_ptr<TsxTileset>& {
    static TilesetManager instance;
    if (instance.m_tsx_tilesets.count(tsx_file_name))
        return instance.m_tsx_tilesets[tsx_file_name];
    else {
        pugi::xml_document xml;
        auto result = xml.load_file(tsx_file_name.c_str());
        if (!result) {
            std::cout << "Error parsing TSX file «" << tsx_file_name << "» : " << result.description() << std::endl;
            std::exit(-1);
        }
        instance.m_tsx_tilesets[tsx_file_name] =  std::make_shared<TsxTileset>(xml.child("tileset"), std::filesystem::path(tsx_file_name).remove_filename().string());
        return instance.m_tsx_tilesets[tsx_file_name];
    }
}


TsxTileset::TsxTileset(const pugi::xml_node& xml_node, const std::string& path) :
name(xml_node.attribute("name").as_string()),
tilewidth(xml_node.attribute("tilewidth").as_uint()),
tileheight(xml_node.attribute("tileheight").as_uint()),
tilecount(xml_node.attribute("tilecount").as_uint()),
columns(xml_node.attribute("columns").as_uint()),
margin(xml_node.attribute("margin").as_uint()),
spacing(xml_node.attribute("spacing").as_uint()) {

    m_image_source = xml_node.child("image").attribute("source").as_string();
#ifdef NS_RESLIB
    m_texture = ns::Res::getTexture(path + m_image_source);
#else
    m_texture = std::make_shared<sf::Texture>();
    m_texture->loadFromFile(path + m_image_source);
#endif

    // parsing tileset properties
    for (const auto& xmlnode_prop : xml_node.child("properties").children()) {
        addProperty(xmlnode_prop);
    }
    // parsing tileset tiles properties and animations
    for (const auto& xmlnode_tile : xml_node.children("tile")) {
        std::uint32_t tile_id =  xmlnode_tile.attribute("id").as_uint();
        for (const auto& xmlnode_tile_prop : xmlnode_tile.child("properties").children())
            m_tile_properties[tile_id].addProperty(xmlnode_tile);

        for (const auto& xmlnode_tile_animframe : xmlnode_tile.child("animation").children()) {
            std::uint32_t id = xmlnode_tile_animframe.attribute("tileid").as_uint();
            unsigned int duration = xmlnode_tile_animframe.attribute("duration").as_uint();
            m_tile_animations[tile_id].frames.push_back({id, duration});
        }
    }
}

auto TsxTileset::getTexture() const -> const sf::Texture & {
    return *m_texture;
}

auto TsxTileset::getTileAnim(std::uint32_t id) -> const TileAnim* {
    if (m_tile_animations.count(id) > 0)
        return &m_tile_animations[id];
    return nullptr;
}


Tileset::Tileset(const pugi::xml_node& xml_node, const std::string& base_path) :
TsxTileset(xml_node, base_path),
firstgid(xml_node.attribute("firstgid").as_uint())
{}

Tileset::Tileset(const std::shared_ptr<TsxTileset>& tsx_tileset, unsigned int first_gid) :
TsxTileset(*tsx_tileset),
firstgid(first_gid)
{}
