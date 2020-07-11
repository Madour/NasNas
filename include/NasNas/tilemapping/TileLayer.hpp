/**
* Created by Modar Nasser on 09/07/2020.
**/


#pragma once

#include <map>
#include <cstdint>
#include "SFML/Graphics.hpp"
#include "NasNas/tilemapping/Layer.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"

namespace ns {
    namespace tm {
        enum class TileTransformation : std::uint8_t {
            HorizontalFlip = 0x8,
            VerticalFlip = 0x4,
            DiagonalFlip = 0x2,
            Rotation90 = HorizontalFlip | DiagonalFlip,
            Rotation180 = HorizontalFlip | VerticalFlip,
            Rotation270 = VerticalFlip | DiagonalFlip,
            None = 0x0
        };

        struct Tile {
            Tile(std::uint32_t tile_gid, std::uint8_t tile_flip) {
                gid = tile_gid;
                flip = tile_flip;
            }
            std::uint32_t gid;
            std::uint8_t flip;
        };

        class TileLayer : public Layer {
        public:
            TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        private:
            unsigned int m_width;
            unsigned int m_height;

            std::vector<Tile> m_tiles;
        };
    }
}
