// Created by Modar Nasser on 01/07/2021.

#pragma once

#include <NasNas/tilemapping/Layer.hpp>
#include <NasNas/tilemapping/LayersContainer.hpp>

namespace ns::tm {

    class GroupLayer : public Layer, public LayersContainer {
    public:
        GroupLayer(const pugi::xml_node& xml_node, TiledMap* tiledmap);

        auto getGlobalBounds() const -> ns::FloatRect override;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    };
}
