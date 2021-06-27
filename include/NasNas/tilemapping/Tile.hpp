// Created by Modar Nasser on 24/06/2021.

#pragma once

#include <optional>

#include "NasNas/core/data/Rect.hpp"
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
        void fill(const pugi::xml_node& xml_node);
    public:
        TileData(std::uint32_t tile_id);
        const std::uint32_t id;
        std::string type;
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
        static std::optional<Tile> None;

        Tile(const TileData& tiledata, const TilesetData& tilesetdata, std::uint32_t tilegid, int posx, int posy,  Flip tileflip=Flip::None);
        auto getTileTexCoo() const -> std::vector<sf::Vector2f>;
        auto getTileTextureRect() const -> ns::FloatRect;
        const TileData& data;
        const TilesetData& tileset;
        const std::uint32_t gid;
        const int x;
        const int y;
        const Flip flip;
    };

    auto operator&(Tile::Flip lhs, Tile::Flip rhs) -> Tile::Flip;
}
