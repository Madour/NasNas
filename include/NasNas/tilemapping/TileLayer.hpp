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
        None = 0x0,
        HorizontalFlip = 0x8,
        VerticalFlip = 0x4,
        DiagonalFlip = 0x2,
        Rotation90 = HorizontalFlip | DiagonalFlip,
        Rotation180 = HorizontalFlip | VerticalFlip,
        Rotation270 = VerticalFlip | DiagonalFlip
    };


    class TileLayer : public Layer {

        struct Tile {
        public:
            Tile(std::uint32_t tile_gid, std::uint8_t tile_flip, const PropertiesContainer* props) :
            gid(tile_gid), flip(tile_flip), properties(props)
            {}
            const PropertiesContainer* properties;
            const std::uint32_t gid;
            const std::uint8_t flip;
        };

        struct AnimatedTileInfo {
            unsigned int index;
            sf::Clock clock;
            std::vector<sf::Vector2u> positions;
        };

    public:
        TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto getTile(int x, int y) -> const Tile&;
        auto getTile(sf::Vector2i pos) -> const Tile&;
        auto getGlobalBounds() -> ns::FloatRect override;

        void update();

    private:
        unsigned int m_width;
        unsigned int m_height;

        std::vector<Tile> m_tiles;
        std::unordered_map<const Tileset*, sf::VertexArray> m_vertices;
        std::map<std::uint32_t, AnimatedTileInfo> m_animated_tiles_pos;
        sf::RenderTexture m_render_texture;
        sf::Sprite m_sprite;

        void addTile(std::uint32_t gid, unsigned int tile_count);
        auto getTileTexCoo(std::uint32_t gid, std::uint8_t transformation) -> std::vector<sf::Vector2f>;
        auto getTileTexCoo(const Tile& tile) -> std::vector<sf::Vector2f>;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
