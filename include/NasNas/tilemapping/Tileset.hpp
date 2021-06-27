/**
* Created by Modar Nasser on 14/07/2020.
**/


#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/core/data/Rect.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/Tile.hpp"

namespace ns::tm {

    class TilesetData : public PropertiesContainer{

        struct TileAnimFrame {
            std::uint32_t tileid;
            int duration;
        };
        struct TileAnim {
            std::vector<TileAnimFrame> frames;
        };

    public:
        TilesetData(const pugi::xml_node& xml_node, const std::string& base_path);
        ~TilesetData();

        auto getTexture() const -> const sf::Texture&;
        auto getTileData(std::uint32_t id) const -> const TileData&;
        auto getTileTexCoo(std::uint32_t id, Tile::Flip flip=Tile::Flip::None) const -> std::vector<sf::Vector2f>;
        auto getTileTextureRect(std::uint32_t id) const -> ns::FloatRect;

        const std::string name;
        const unsigned int tilewidth;
        const unsigned int tileheight;
        const unsigned int tilecount;
        const unsigned int columns;
        const unsigned int margin;
        const unsigned int spacing;

    private:
        std::string m_image_source;
        sf::Texture* m_texture;
        std::vector<TileData> m_tiles_data;
    };

    class Tileset {
    public:
        Tileset(const TilesetData& tilesetdata, unsigned int first_gid);
        const TilesetData& data;
        const unsigned int firstgid;
    };

    class TsxTilesetsManager {
    public:
        static auto get(const std::string& tsx_file_name) -> const TilesetData&;

    private:
        explicit TsxTilesetsManager() = default;
        std::unordered_map<std::string, TilesetData> m_shared_tilesets;
    };

}
