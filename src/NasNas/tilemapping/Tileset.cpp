/**
* Created by Modar Nasser on 14/07/2020.
**/

#include "NasNas/core/data/Utils.hpp"
#include "NasNas/tilemapping/Tileset.hpp"
#include "NasNas/tilemapping/Tile.hpp"
#ifdef NS_RESLIB
#include "NasNas/reslib/ResourceManager.hpp"
#endif

using namespace ns;
using namespace ns::tm;

TsxTilesetsManager::TsxTilesetsManager() = default;

auto TsxTilesetsManager::get(const std::string& tsx_file_name) -> const std::shared_ptr<TilesetData>& {
    static TsxTilesetsManager instance;
    if (instance.m_shared_tilesets.count(tsx_file_name))
        return instance.m_shared_tilesets[tsx_file_name];
    else {
        pugi::xml_document xml;
        auto result = xml.load_file(tsx_file_name.c_str());
        if (!result) {
            std::cout << "Error parsing TSX file «" << tsx_file_name << "» : " << result.description() << std::endl;
            std::exit(-1);
        }
        instance.m_shared_tilesets[tsx_file_name] =  std::make_shared<TilesetData>(xml.child("tileset"), utils::path::getPath(tsx_file_name));
        return instance.m_shared_tilesets[tsx_file_name];
    }
}


TilesetData::TilesetData(const pugi::xml_node& xml_node, const std::string& path) :
PropertiesContainer(xml_node.child("properties")),
name(xml_node.attribute("name").as_string()),
tilewidth(xml_node.attribute("tilewidth").as_uint()),
tileheight(xml_node.attribute("tileheight").as_uint()),
tilecount(xml_node.attribute("tilecount").as_uint()),
columns(xml_node.attribute("columns").as_uint()),
margin(xml_node.attribute("margin").as_uint()),
spacing(xml_node.attribute("spacing").as_uint())
{
    m_image_source = xml_node.child("image").attribute("source").as_string();
#ifdef NS_RESLIB
    m_texture = &ns::Res::getTexture(path+m_image_source);
#else
    m_texture = new sf::Texture();
    m_texture->loadFromFile(path + m_image_source);
#endif

    // parsing tileset tiles properties and animations
    for (const auto& xmlnode_tile : xml_node.children("tile")) {
        std::uint32_t tile_id = xmlnode_tile.attribute("id").as_uint();
        m_tiles.emplace(tile_id, xmlnode_tile);
    }
}

TilesetData::~TilesetData()
#ifdef NS_RESLIB
    = default;
#else
{
    if(m_texture && m_texture->getSize().x > 0 && m_texture->getSize().y > 0) {
        delete (m_texture);
        m_texture = nullptr;
    }
}
#endif

auto TilesetData::getTexture() const -> const sf::Texture & {
    return *m_texture;
}

auto TilesetData::getTile(std::uint32_t id) const -> const TileData& {
    if (m_tiles.count(id) > 0) return m_tiles.at(id);
    m_tiles.emplace(id, TileData(id));
    return m_tiles.at(id);
}

auto TilesetData::getTileTextureRect(unsigned int id) const -> ns::FloatRect {
    auto tx = static_cast<float>((id % columns) * (tilewidth + spacing) + margin);
    auto ty = static_cast<float>((id / columns) * (tileheight + spacing) + margin);
    return {sf::Vector2f(tx, ty), sf::Vector2f(static_cast<float>(tilewidth), static_cast<float>(tileheight))};
}


Tileset::Tileset(const pugi::xml_node& xml_node, const std::string& base_path) :
TilesetData(xml_node, base_path),
firstgid(xml_node.attribute("firstgid").as_uint())
{}

Tileset::Tileset(const std::shared_ptr<TilesetData>& shared_tileset, unsigned int first_gid) :
TilesetData(*shared_tileset),
firstgid(first_gid)
{}
