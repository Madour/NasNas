/**
* Created by Modar Nasser on 14/07/2020.
**/


#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"

namespace ns::tm {

    class TilesetManager {
    public:
        static auto get(const std::string& tsx_file_name) -> const std::shared_ptr<TsxTileset>&;

    private:
        explicit TilesetManager();
        std::unordered_map<std::string, std::shared_ptr<TsxTileset>> m_tsx_tilesets;
    };

    class TsxTileset : public PropertiesContainer{

        struct TileAnimFrame {
            std::uint32_t tileid;
            unsigned int duration;
        };
        struct TileAnim {
            std::vector<TileAnimFrame> frames;
        };

    public:
        TsxTileset(const pugi::xml_node& xml_node, const std::string& base_path);

        auto getTexture() const -> const sf::Texture&;
        auto getTileAnim(std::uint32_t id) -> const TileAnim*;

        const std::string name;
        const unsigned int tilewidth;
        const unsigned int tileheight;
        const unsigned int tilecount;
        const unsigned int columns;
        const unsigned int margin;
        const unsigned int spacing;

    private:
        std::string m_image_source;
        std::shared_ptr<sf::Texture> m_texture;
        std::map<std::uint32_t, PropertiesContainer> m_tile_properties;
        std::map<std::uint32_t, TileAnim> m_tile_animations;
    };

    class Tileset : public TsxTileset {
    public:
        Tileset(const pugi::xml_node& xml_node, const std::string& base_path);
        Tileset(const std::shared_ptr<TsxTileset>& tsx_tileset, unsigned int first_gid);

        const unsigned int firstgid;
    };

}
