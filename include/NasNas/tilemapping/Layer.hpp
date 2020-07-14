/**
* Created by Modar Nasser on 11/07/2020.
**/


#pragma once

#include "NasNas/thirdparty/pugixml.hpp"
#include "NasNas/data/Drawable.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"
#include "NasNas/tilemapping/TiledMap.hpp"

namespace ns::tm {

    class Layer : public PropertiesContainer {
    public:
        Layer(const pugi::xml_node& xml_node, TiledMap* tiledmap);
        auto getId() const -> unsigned int;
        auto getName() -> std::string&;
        auto isVisible() const -> bool;
        void setVisible(bool value);

    protected:
        TiledMap* m_tiledmap = nullptr;
        sf::Vector2f m_position = {0, 0};

    private:
        unsigned int m_id;
        std::string m_name;
        bool m_visible = true;
        float m_opacity = 1.f;
    };

}
