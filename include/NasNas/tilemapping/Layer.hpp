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

    class Layer : public PropertiesContainer, public sf::Drawable, public sf::Transformable {
        friend LayersContainer;
    public:
        Layer(const pugi::xml_node& xml_node, TiledMap* tiledmap);
        auto getId() const -> unsigned int;
        auto getName() const -> const std::string&;

        auto isVisible() const -> bool;
        void setVisible(bool value);

        auto getOffset() const -> const sf::Vector2f&;
        auto getTotalOffset() const -> sf::Vector2f;

        auto getParallaxFactor() const -> const sf::Vector2f&;
        auto getTotalParallaxFactor() const -> sf::Vector2f;

        auto getTintColor() const -> const sf::Color&;

        virtual auto getGlobalBounds() const -> ns::FloatRect;

    protected:
        const TiledMap* m_tiledmap = nullptr;
        const GroupLayer* m_parent_group = nullptr;

    private:
        unsigned int m_id;
        std::string m_name;
        bool m_visible = true;
        float m_opacity = 1.f;
        sf::Color m_tintcolor = sf::Color::White;
        sf::Vector2f m_offset;
        sf::Vector2f m_parallax_factor = {1.f, 1.f};
    };

}
