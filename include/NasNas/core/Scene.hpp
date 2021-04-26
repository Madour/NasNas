/**
* Created by Modar Nasser on 19/04/2020.
**/


#pragma once

#include <map>
#include "NasNas/core/data/AppComponent.hpp"
#include "NasNas/core/Layer.hpp"

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
        explicit Scene(std::string name);

        Scene(const Scene&) = delete;
        Scene(Scene&&) = default;

        /**
         * \brief Adds a new layer to the scene
         * \param layer_name Layer name
         * \param order The order of render of the layer
         */
        void addLayer(const std::string& name, int order);

        /**
         * \brief Removes and clears the Layer of the given order
         *
         * \param order Layer order to remove
         */
        void removeLayer(int order);

        /**
         * \brief Removes and clears the Layer of the given name
         *
         * \param name Layer name to remove
         */
        void removeLayer(const std::string& name);

        /**
         * \brief Returns the layer of the given order
         *
         * \param order The order of the layer to get
         *
         * \return Pointer to Layer object
         */
        auto getLayer(int order) -> Layer&;

        /**
         * \brief Returns the layer of the given name
         *
         * \param name The name of the layer to get
         *
         * \return Reference to the requested Layer object
         */
        auto getLayer(const std::string& name) -> Layer&;

        /**
         * \brief Returns the default Scene Layer
         * Default layer will always be drawn first, before any other layer.
         *
         * \return Reference to the default Layer object
         */
         auto getDefaultLayer() -> Layer&;

    private:
        friend App; friend Camera;

        std::string m_name;         ///< Scene name
        std::map<int, Layer> m_layers;
        Layer m_default_layer;
        ns::FloatRect m_render_bounds;

        /**
        * \brief Temporary links the Scene to a Camera for rendering
        *
        * \param camera Camera object to link
        */
        void temporaryLinkCamera(Camera* camera);

        /**
         * \brief Draws the Scene sprite on the AppWindow
         *
         * \param target AppWindow
         * \param states Render states
         */
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void drawVariant(const Layer::DrawablesTypes& variant, sf::RenderTarget& target, sf::RenderStates states) const;
    };

}
