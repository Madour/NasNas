/**
* Created by Modar Nasser on 09/07/2020.
**/


#pragma once

#include <map>
#include <memory>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/Tileset.hpp"

namespace ns::tm {

    class TiledMap : public PropertiesContainer {
    public:
        TiledMap();

        auto loadFromFile(const std::string& file_name) -> bool;
        auto loadFromString(const std::string& data) -> bool;

        auto getSize() -> const sf::Vector2u&;
        auto getTileSize() -> const sf::Vector2u&;
        auto getTileTileset(unsigned int gid) -> const std::unique_ptr<Tileset>&;

        auto allTilesets() -> const std::vector<std::unique_ptr<Tileset>>&;

        auto getTileLayer(const std::string& name) -> const std::shared_ptr<TileLayer>&;
        auto getObjectLayer(const std::string& name) -> const std::shared_ptr<ObjectLayer>&;
    private:
        pugi::xml_node m_xmlnode_map;
        std::string m_file_name;
        std::filesystem::path m_file_relative_path;

        sf::Vector2u m_size;
        sf::Vector2u m_tilesize;

        std::vector<std::unique_ptr<Tileset>> m_tilesets;
        std::map<std::pair<int, std::string>, std::shared_ptr<TileLayer>> m_layers;
        std::map<std::pair<int, std::string>, std::shared_ptr<ObjectLayer>> m_objectlayers;

        void load(const pugi::xml_document& xml);
    };

}
