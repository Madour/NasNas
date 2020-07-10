/**
* Created by Modar Nasser on 19/04/2020.
**/

#pragma once

#include <NasNas/data/AppComponent.hpp>
#include <NasNas/core/Layers.hpp>

namespace ns {
    class Camera;
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
        explicit Scene(const std::string& name);

        /**
         * \brief Adds a given layer to the scene
         *
         * \param layer Raw pointer to the Layer to add
         * \param order The order of render of the layer on the scene
         *
         * \see getLayer
         */
        void addLayer(Layer* layer, int order);

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
         * \brief Returns the layer of the given name
         *
         * \param name The name of the layer to get
         *
         * \return Pointer to Layer object
         */
        auto getLayer(const std::string& name) -> Layer*;

        /**
         * \brief Temporary links the Scene to a Camera for rendering
         *
         * \param camera Camera object to link
         */
        void temporaryLinkCamera(Camera* camera);

    private:
        friend App; friend Camera;

        std::string m_name;         ///< Scene name
        /// Map of Layer objects of the Scene sorted by their order
        std::map<std::pair<int, std::string>, std::shared_ptr<Layer>> m_layers;
        ns::FloatRect render_bounds;

        /**
         * \brief Draws the Scene sprite on the AppWindow
         *
         * \param target AppWindow
         * \param states Render states
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
