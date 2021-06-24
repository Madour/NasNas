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

    class TsxTilesetsManager {
    public:
        static auto get(const std::string& tsx_file_name) -> const std::shared_ptr<TilesetData>&;

    private:
        explicit TsxTilesetsManager();
        std::unordered_map<std::string, std::shared_ptr<TilesetData>> m_shared_tilesets;
    };

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
        auto getTile(std::uint32_t id) const -> const TileData&;
        auto getTileTextureRect(unsigned int id) const -> ns::FloatRect;

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
        mutable std::map<std::uint32_t, TileData> m_tiles;
    };

    class Tileset : public TilesetData {
    public:
        Tileset(const pugi::xml_node& xml_node, const std::string& base_path);
        Tileset(const std::shared_ptr<TilesetData>& shared_tileset, unsigned int first_gid);
        const unsigned int firstgid;
    };

}
