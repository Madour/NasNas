// Created by Modar Nasser on 24/06/2021.

#include "NasNas/tilemapping/Tile.hpp"

using namespace ns;
using namespace ns::tm;


TileData::TileData(const pugi::xml_node& xml_node) :
id(xml_node.attribute("id").as_uint()),
type(xml_node.attribute("type").as_string())
{
    parseProperties(xml_node.child("properties"));
    for (const auto& xmlnode_tile_animframe : xml_node.child("animation").children()) {
        std::uint32_t otherid = xmlnode_tile_animframe.attribute("tileid").as_uint();
        int duration = xmlnode_tile_animframe.attribute("duration").as_int();
        animframes.push_back({otherid, duration});
    }
}

TileData::TileData(std::uint32_t id) :
id(id)
{}

Tile::Tile(const TileData& data, std::uint32_t gid, std::uint8_t flip, const Tileset& tileset) :
data(data),
gid(gid),
flip(flip),
tileset(tileset)
{}
