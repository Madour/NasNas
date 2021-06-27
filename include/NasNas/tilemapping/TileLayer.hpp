/**
* Created by Modar Nasser on 09/07/2020.
**/


#pragma once

#include <unordered_map>
#include <optional>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "NasNas/core/graphics/Drawable.hpp"
#include "NasNas/tilemapping/Layer.hpp"
#include "NasNas/tilemapping/Tile.hpp"

namespace ns::tm {
    class TiledMap;

    class TileLayer : public Layer {

        struct AnimatedTileInfo {
            unsigned int index;
            sf::Clock clock;
            std::vector<sf::Vector2u> positions;
        };

    public:
        TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto getTile(int x, int y) const -> const std::optional<Tile>&;
        auto getTile(sf::Vector2i pos) const -> const std::optional<Tile>&;
        auto getGlobalBounds() const -> ns::FloatRect override;

        void update();

    private:
        int m_width;
        int m_height;

        std::unordered_map<unsigned, std::optional<Tile>> m_tiles;
        std::unordered_map<const Tileset*, sf::VertexArray> m_vertices;
        std::map<std::uint32_t, AnimatedTileInfo> m_animated_tiles_pos;
        sf::RenderTexture m_render_texture;
        sf::Sprite m_sprite;

        void addTile(std::uint32_t gid, int tile_count);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
