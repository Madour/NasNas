// Created by Modar Nasser on 24/06/2021.

#include "NasNas/tilemapping/Tile.hpp"
#include "NasNas/tilemapping/Tileset.hpp"

using namespace ns;
using namespace ns::tm;

TileData::TileData(std::uint32_t tile_id) :
id(tile_id)
{}

void TileData::fill(const pugi::xml_node& xml_node) {
    type = xml_node.attribute("type").as_string();
    parseProperties(xml_node.child("properties"));
    for (const auto& xmlnode_tile_animframe : xml_node.child("animation").children()) {
        std::uint32_t otherid = xmlnode_tile_animframe.attribute("tileid").as_uint();
        int duration = xmlnode_tile_animframe.attribute("duration").as_int();
        animframes.push_back({otherid, duration});
    }
}

std::optional<Tile> Tile::None = std::nullopt;
std::uint32_t Tile::gidmask = 0x1fffffff;

Tile::Tile(const TileData& tiledata, const TilesetData& tilesetdata, std::uint32_t tilegid, int posx, int posy, Flip tileflip) :
data(tiledata),
tileset(tilesetdata),
gid(tilegid),
x(posx),
y(posy),
flip(tileflip)
{}

auto Tile::getTileTextureRect() const -> ns::FloatRect {
    return tileset.getTileTextureRect(data.id);
}

auto Tile::getTileTexCoo() const -> std::vector<sf::Vector2f> {
    return tileset.getTileTexCoo(data.id, flip);
}

auto ns::tm::operator&(Tile::Flip lhs, Tile::Flip rhs) -> Tile::Flip {
    return static_cast<Tile::Flip>(
            static_cast<std::underlying_type<Tile::Flip>::type>(lhs) &
            static_cast<std::underlying_type<Tile::Flip>::type>(rhs)
    );
}

auto ns::tm::operator==(const std::optional<Tile>& lhs, const std::optional<Tile>& rhs) -> bool {
    if (!lhs && !rhs) return true;
    if (!lhs && rhs || lhs && !rhs) return false;
    return (lhs->gid == rhs->gid && lhs->x == rhs->x && lhs->y == rhs->y);
}

auto ns::tm::operator!=(const std::optional<Tile>& lhs, const std::optional<Tile>& rhs) -> bool {
    return !ns::tm::operator==(lhs, rhs);
}

