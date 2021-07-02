/**
* Created by Modar Nasser on 09/07/2020.
**/


#pragma once

#include <unordered_map>
#include <optional>
#include <cstdint>
#include <SFML/Graphics.hpp>
#include "NasNas/core/graphics/Renderable.hpp"
#include "NasNas/tilemapping/Layer.hpp"
#include "NasNas/tilemapping/Tile.hpp"

namespace ns::tm {
    class TiledMap;

    class TileLayer : public Layer, public Renderable {

        struct AnimatedTileInfo {
            unsigned int index;
            sf::Clock clock;
            std::vector<sf::Vector2u> positions;
        };

    public:
        TileLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto getTile(int x, int y) const -> const std::optional<Tile>&;
        auto getTile(sf::Vector2i pos) const -> const std::optional<Tile>&;
        void setTile(int x, int y, std::uint32_t gid);

        void update();

    private:
        int m_width;
        int m_height;

        std::vector<std::optional<Tile>> m_tiles;
        std::map<std::uint32_t, AnimatedTileInfo> m_animated_tiles_pos;
        std::unordered_map<const Tileset*, sf::VertexArray> m_vertices;
        sf::RenderTexture m_render_texture;
        sf::Sprite m_sprite;

        void addTile(int tile_index, std::uint32_t gid);
        void updateTileTexCoo(const Tileset& tileset, unsigned tile_index, const std::vector<sf::Vector2f>& tex_coo);

        void render() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
