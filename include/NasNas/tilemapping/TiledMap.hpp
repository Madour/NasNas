/**
* Created by Modar Nasser on 09/07/2020.
**/


#pragma once

#include <string>
#include <vector>

#include <SFML/System/Vector2.hpp>

#include <NasNas/tilemapping/LayersContainer.hpp>
#include <NasNas/tilemapping/PropertiesContainer.hpp>
#include <NasNas/tilemapping/Tileset.hpp>

namespace pugi {
    class xml_document;
}

namespace ns::tm {

    class TiledMap : public LayersContainer, public PropertiesContainer {
    public:
        TiledMap();

        auto loadFromFile(const std::string& file_name) -> bool;
        auto loadFromString(const std::string& data) -> bool;

        auto getTMXFilePath() const -> const std::string&;

        auto getSize() const -> const sf::Vector2f&;
        auto getGridSize() const -> const sf::Vector2u&;
        auto getTileSize() const -> const sf::Vector2u&;

        auto allTilesets() const -> const std::vector<Tileset>&;
        auto getTileTileset(unsigned int gid) const -> const Tileset&;

        void setCamera(const Camera& cam);

        void update();

    private:
        void load(const pugi::xml_document& xml);

        std::string m_file_name;
        std::string m_file_relative_path;

        sf::Vector2u m_gridsize;
        sf::Vector2u m_tilesize;
        sf::Vector2f m_size;

        std::vector<Tileset> m_tilesets;
        std::vector<TilesetData> m_tilesets_data;

        const Camera* m_camera = nullptr;
    };

}
