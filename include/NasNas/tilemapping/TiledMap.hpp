/**
* Created by Modar Nasser on 09/07/2020.
**/

#pragma once

#include <map>
#include "SFML/Graphics.hpp"
#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/tilemapping/TileLayer.hpp"
#include "NasNas/tilemapping/PropertyTypes.hpp"

namespace ns {
    class TiledMap {
    public:
        TiledMap();
        auto loadFromFile(const std::string& file_name) -> bool;
        auto loadFromString(const std::string& data) -> bool;

    private:
        pugi::xml_document m_xml;

        bool m_ready = false;

        int m_width = 0;
        int m_height = 0;
        int m_tilewidth = 0;
        int m_tileheight = 0;

        std::unordered_map<std::string, TileLayer*> m_layers;
        std::unordered_map<std::string, PropertyTypes> m_properties;

        void load();
    };

}
