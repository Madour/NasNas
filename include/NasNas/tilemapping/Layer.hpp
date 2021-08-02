/**
* Created by Modar Nasser on 11/07/2020.
**/


#pragma once

#include "NasNas/thirdparty/pugixml.hpp"

#include "NasNas/core/data/Rect.hpp"
#include "NasNas/tilemapping/PropertiesContainer.hpp"

namespace ns::tm {
    class TiledMap;
    class GroupLayer;
    class LayersContainer;

    class Layer : public PropertiesContainer, public sf::Drawable {
    public:
        Layer(const pugi::xml_node& xml_node, TiledMap* tiledmap);
        auto getId() const -> unsigned int;
        auto getName() const -> const std::string&;

        auto getPosition() const -> sf::Vector2f;
        void setPosition(float x, float y);
        void setPosition(sf::Vector2f position);
        void move(float x, float y);

        auto isVisible() const -> bool;
        void setVisible(bool value);

        auto getParallaxFactor() const -> const sf::Vector2f&;
        auto getTotalParallaxFactor() const -> sf::Vector2f;

        auto getOffset() const -> const sf::Vector2f&;

        virtual auto getGlobalBounds() const -> ns::FloatRect;

    protected:
        friend LayersContainer;
        const TiledMap& m_tiledmap;
        const GroupLayer* m_parent_group = nullptr;
        sf::Transformable m_transformable;
        sf::Color m_tintcolor = sf::Color::White;
        sf::Vector2f m_parallax_factor = {1.f, 1.f};

    private:
        unsigned int m_id;
        std::string m_name;
        bool m_visible = true;
        float m_opacity = 1.f;
        sf::Vector2f m_offset;
    };

}
