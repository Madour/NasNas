// Created by Modar Nasser on 24/06/2021.

#include "NasNas/tilemapping/Tile.hpp"
#include "NasNas/tilemapping/Tileset.hpp"

using namespace ns;
using namespace ns::tm;


TileData::TileData(const pugi::xml_node& xml_node, const TilesetData* tilesetdata) :
id(xml_node.attribute("id").as_uint()),
type(xml_node.attribute("type").as_string()),
tileset(*tilesetdata)
{
    parseProperties(xml_node.child("properties"));
    for (const auto& xmlnode_tile_animframe : xml_node.child("animation").children()) {
        std::uint32_t otherid = xmlnode_tile_animframe.attribute("tileid").as_uint();
        int duration = xmlnode_tile_animframe.attribute("duration").as_int();
        animframes.push_back({otherid, duration});
    }
}

std::optional<Tile> Tile::None = std::nullopt;

TileData::TileData(std::uint32_t id, const TilesetData* tilesetdata) :
id(id),
tileset(*tilesetdata)
{}

Tile::Tile(const TileData& tiledata, std::uint32_t tilegid, int posx, int posy, Flip tileflip) :
data(tiledata),
gid(tilegid),
x(posx),
y(posy),
flip(tileflip)
{}

auto Tile::getTexCoo() -> std::vector<sf::Vector2f> {
    return data.tileset.getTileTexCoo(data.id, flip);
}

auto Tile::getTexRect() -> ns::FloatRect {
    return data.tileset.getTileTextureRect(data.id);
}

auto ns::tm::operator&(Tile::Flip lhs, Tile::Flip rhs) -> Tile::Flip {
    return static_cast<Tile::Flip>(
            static_cast<std::underlying_type<Tile::Flip>::type>(lhs) &
            static_cast<std::underlying_type<Tile::Flip>::type>(rhs)
    );
}
