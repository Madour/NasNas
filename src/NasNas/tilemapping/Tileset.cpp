/**
* Created by Modar Nasser on 14/07/2020.
**/

#include "NasNas/core/data/Utils.hpp"
#include "NasNas/tilemapping/Tileset.hpp"
#ifdef NS_RESLIB
#include "NasNas/reslib/ResourceManager.hpp"
#endif

using namespace ns;
using namespace ns::tm;


TilesetData::TilesetData(const pugi::xml_node& xml_node, const std::string& path) :
name(xml_node.attribute("name").as_string()),
tilewidth(xml_node.attribute("tilewidth").as_uint()),
tileheight(xml_node.attribute("tileheight").as_uint()),
tilecount(xml_node.attribute("tilecount").as_uint()),
columns(xml_node.attribute("columns").as_uint()),
margin(xml_node.attribute("margin").as_uint()),
spacing(xml_node.attribute("spacing").as_uint()),
m_image_source(xml_node.child("image").attribute("source").as_string())
{
    parseProperties(xml_node.child("properties"));

#ifdef NS_RESLIB
    m_texture = &ns::Res::getTexture(path+m_image_source);
#else
    m_texture = new sf::Texture();
    m_texture->loadFromFile(path + m_image_source);
#endif

    m_tiles_data.reserve(tilecount);
    for (std::uint32_t i = 0; i < tilecount; ++i){
        m_tiles_data.emplace_back(i);
    }
    for (const auto& xmlnode_tile : xml_node.children("tile")) {
        std::uint32_t tile_id = xmlnode_tile.attribute("id").as_uint();
        m_tiles_data[tile_id].fill(xmlnode_tile);
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

auto TilesetData::getTexture() const -> const sf::Texture& {
    return *m_texture;
}

auto TilesetData::getTileData(std::uint32_t id) const -> const TileData& {
    return m_tiles_data[id];
}

auto TilesetData::getTileTexCoo(std::uint32_t id, Tile::Flip flip) const -> std::vector<sf::Vector2f> {
    auto texture_rect = getTileTextureRect(id);

    auto coords = std::vector<sf::Vector2f>(4);
    coords[0] = sf::Vector2f(texture_rect.topleft());
    coords[1] = sf::Vector2f(texture_rect.topright());
    coords[2] = sf::Vector2f(texture_rect.bottomright());
    coords[3] = sf::Vector2f(texture_rect.bottomleft());

    if ((flip & Tile::Flip::VerticalFlip) != Tile::Flip::None) {
        auto temp = coords[0];
        coords[0].y = coords[3].y;  coords[1].y = coords[2].y;
        coords[3].y = temp.y;       coords[2].y = temp.y;
    }
    if ((flip & Tile::Flip::HorizontalFlip) != Tile::Flip::None) {
        auto temp = coords[0];
        coords[0].x = coords[1].x; coords[1].x = temp.x;
        coords[3].x = coords[0].x; coords[2].x = coords[1].x;
    }
    if ((flip & Tile::Flip::DiagonalFlip) != Tile::Flip::None) {
        int i1 = 1, i2 = 3;
        if (flip == Tile::Flip::Rotation90 ||
            flip == Tile::Flip::Rotation270) {
            i1 = 0; i2 = 2;
        }
        auto temp = coords[i1];
        coords[i1] = coords[i2];
        coords[i2] = temp;
    }
    return coords;
}


auto TilesetData::getTileTextureRect(std::uint32_t id) const -> ns::IntRect {
    auto tx = (id % columns) * (tilewidth + spacing) + margin;
    auto ty = (id / columns) * (tileheight + spacing) + margin;
    return ns::IntRect(tx, ty, tilewidth, tileheight);
}


Tileset::Tileset(const TilesetData& tilesetdata, unsigned int first_gid) :
data(tilesetdata),
firstgid(first_gid)
{}


auto TsxTilesetsManager::get(const std::string& tsx_file_name) -> const TilesetData& {
    static TsxTilesetsManager instance;
    if (instance.m_shared_tilesets.count(tsx_file_name))
        return instance.m_shared_tilesets.at(tsx_file_name);
    else {
        pugi::xml_document xml;
        auto result = xml.load_file(tsx_file_name.c_str());
        if (!result) {
            std::cout << "Error parsing TSX file «" << tsx_file_name << "» : " << result.description() << std::endl;
            std::exit(-1);
        }
        instance.m_shared_tilesets.emplace(tsx_file_name, TilesetData(xml.child("tileset"), utils::path::getPath(tsx_file_name)));
        return instance.m_shared_tilesets.at(tsx_file_name);
    }
}
