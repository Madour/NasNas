// Created by Modar Nasser on 24/06/2021.

#pragma once

#include "NasNas/tilemapping/PropertiesContainer.hpp"

namespace ns::tm {
    class TilesetData;
    class Tileset;

    class TileData : public PropertiesContainer {
        friend TilesetData;
        struct AnimFrame {
            std::uint32_t tileid;
            int duration;
        };
        explicit TileData(std::uint32_t id);
    public:
        explicit TileData(const pugi::xml_node& xml_node);
        const std::uint32_t id;
        const std::string type;
        std::vector<AnimFrame> animframes;
    };

    struct Tile {
        Tile(const TileData& data, std::uint32_t gid, std::uint8_t flip, const Tileset& tileset);
        const TileData& data;
        const std::uint32_t gid;
        const std::uint8_t flip;
        const Tileset& tileset;
    };
}
