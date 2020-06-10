/**
* Created by Modar Nasser on 19/04/2020.
**/

#pragma once

#include <NasNas/data/AppComponent.hpp>
#include <NasNas/core/Layers.hpp>

namespace ns {

    class Scene : public sf::Drawable {
    public:
        friend App;
        Scene(int width, int height);

        /**
         * \brief Adds a given layer to the scene
         *
         * \param layer The layer to add
         * \param order The order of the layer on the scene
         *
         * \see getLayer
         */
        void addLayer(const std::shared_ptr<Layer>& layer, int order);
        void addLayer(std::shared_ptr<Layer>& layer, int order);

        /**
         * \brief Returns the layer of the given order
         *
         * \param order The order of the layer you want to get
         * \return Returns the layer
         */
        auto getLayer(int order) -> Layer*;

        auto getWidth() -> int;
        auto getHeight() -> int;


    private:
        std::map<int, std::shared_ptr<Layer>> m_layers;
        sf::RenderTexture m_render_texture;
        sf::Sprite m_sprite;
        sf::Color m_clear_color = sf::Color::Transparent;
        void render();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
