/**
* Created by Modar Nasser on 09/07/2020.
**/


#pragma once

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"

namespace ns::tm {

    class TileLayer;

    class TiledMap : public PropertiesContainer {
    public:
        TiledMap();
        auto loadFromFile(const std::string& file_name) -> bool;
        auto loadFromString(const std::string& data) -> bool;

    private:
        pugi::xml_node m_xml_node;

        bool m_ready = false;

        unsigned int m_width = 0;
        unsigned int m_height = 0;
        unsigned int m_tilewidth = 0;
        unsigned int m_tileheight = 0;

        std::map<std::pair<int, std::string>, std::shared_ptr<TileLayer>> m_layers;

        void load(const pugi::xml_document& xml);
    };

}
