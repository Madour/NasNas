/**
* Created by Modar Nasser on 11/07/2020.
**/


#pragma once

#include <iostream>
#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"

namespace ns {
    namespace tm {

        class Layer : public PropertiesContainer {
        public:
            Layer(const pugi::xml_node& xml_node, TiledMap* tiledmap);
            auto getId() -> int;
            auto getName() -> std::string&;
            auto isVisible() -> bool;
            void setVisible(bool value);

        protected:
            pugi::xml_node m_xml_node;
            TiledMap* m_tiledmap = nullptr;

        private:
            unsigned int m_id;
            std::string m_name;
            bool m_visible = true;
            float m_opacity = 1.f;
            sf::Vector2f m_position = {0, 0};
        };

    }
}
