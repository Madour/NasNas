/**
* Created by Modar Nasser on 09/07/2020.
**/


#pragma once

#include <unordered_map>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "NasNas/data/Drawable.hpp"
#include "NasNas/tilemapping/Layer.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"

namespace ns::tm {

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


    class TileLayer : public Layer, public ns::Drawable {
    public:
        TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto getPosition() -> sf::Vector2f override;
        auto getGlobalBounds() -> ns::FloatRect override;
        void move(float offsetx, float offsety) override;

    private:
        unsigned int m_width;
        unsigned int m_height;

        std::vector<Tile> m_tiles;
        //std::unordered_map<const Tileset*, std::vector<sf::Vertex>> m_vertices;
        std::unordered_map<const Tileset*, sf::VertexArray> m_vertices;

        void addTile(unsigned int gid, unsigned int tile_count);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
