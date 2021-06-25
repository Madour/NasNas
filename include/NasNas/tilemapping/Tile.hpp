// Created by Modar Nasser on 24/06/2021.

#pragma once

#include <optional>

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
        explicit TileData(std::uint32_t id, const TilesetData* tilesetdata);
    public:
        explicit TileData(const pugi::xml_node& xml_node, const TilesetData* tilesetdata);
        const std::uint32_t id;
        const std::string type;
        const TilesetData& tileset;
        std::vector<AnimFrame> animframes;
    };

    struct Tile {
        enum class Flip : std::uint8_t {
            None = 0x0,
            HorizontalFlip = 0x8,
            VerticalFlip = 0x4,
            DiagonalFlip = 0x2,
            Rotation90 = HorizontalFlip | DiagonalFlip,
            Rotation180 = HorizontalFlip | VerticalFlip,
            Rotation270 = VerticalFlip | DiagonalFlip
        };
        Tile(const TileData& data, std::uint32_t gid, Flip flip);
        const TileData& data;
        const std::uint32_t gid;
        const Flip flip;
        static std::optional<Tile> None;
    };

    auto operator&(Tile::Flip lhs, Tile::Flip rhs) -> Tile::Flip;
}
