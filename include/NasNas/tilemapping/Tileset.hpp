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
        static auto get(const std::string& tsx_file_name) -> const TsxTileset&;
    private:
        static std::unordered_map<std::string, std::shared_ptr<TsxTileset>> m_tsx_tilesets;
    };

    class TsxTileset : public PropertiesContainer{
    public:
        explicit TsxTileset(const pugi::xml_node& xml_node, const std::string& base_path);
        auto getTexture() const -> const sf::Texture&;

        const std::string name;
        const unsigned int tilewidth;
        const unsigned int tileheight;
        const unsigned int tilecount;
        const unsigned int columns;

    private:
        std::string m_image_source;
        std::shared_ptr<sf::Texture> m_texture;
        std::map<unsigned int, PropertiesContainer> m_tile_properties;
    };

    class Tileset : public TsxTileset {
    public:
        Tileset(const pugi::xml_node& xml_node, const std::string& base_path);
        Tileset(const TsxTileset& tsx_tileset, unsigned int first_gid);

        const unsigned int firstgid;
    };

}
