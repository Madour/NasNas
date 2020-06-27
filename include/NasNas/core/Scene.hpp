/**
* Created by Modar Nasser on 19/04/2020.
**/

#pragma once

#include <NasNas/data/AppComponent.hpp>
#include <NasNas/core/Layers.hpp>

namespace ns {

    class Scene : public sf::Drawable {
    public:
        /**
         * \brief Constructs a Scene object
         *
         * A Scene contains multiple ordered Layer objects.
         * The Layer objects with the lower orders will render their drawables first on the Scene.
         *
         * \param width Width of the Scene
         * \param height Height of the Scene
         */
        Scene(int width, int height);

        /**
         * \brief Adds a given layer to the scene
         *
         * \param layer Shared pointer to the Layer to add
         * \param order The order of render of the layer on the scene
         *
         * \see getLayer
         */
        void addLayer(const std::shared_ptr<Layer>& layer, int order);

        /**
         * \brief Adds a given layer to the scene
         *
         * \param layer Shared pointer to the Layer to add
         * \param order The order of render of the layer on the scene
         *
         * \see getLayer
         */
        void addLayer(std::shared_ptr<Layer>& layer, int order);

        /**
         * \brief Returns the layer of the given order
         *
         * \param order The order of the layer to get
         *
         * \return Pointer to Layer object
         */
        auto getLayer(int order) -> Layer*;

        /**
         * \brief Get the width of the Scene
         *
         * \return Scene width
         */
        auto getWidth() -> int;

        /**
         * \brief Get the height of the Scene
         *
         * \return Scene height
         */
        auto getHeight() -> int;

    private:
        friend App;
        std::map<int, std::shared_ptr<Layer>> m_layers;     ///< Map of Layer objects of the Scene sorted by their order
        sf::Color m_clear_color = sf::Color::Transparent;   ///< Clear color of the Scene render texture
        sf::RenderTexture m_render_texture;                 ///< Scene render texture
        sf::Sprite m_sprite;                                ///< Scene sprite

        /**
         * \brief Render all the Layer objects on the Scene render texture and updates Scene sprite
         */
        void render();

        /**
         * \brief Draws the Scene sprite on the AppWindow
         *
         * \param target AppWindow
         * \param states Render states
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
