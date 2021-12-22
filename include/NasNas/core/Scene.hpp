/**
* Created by Modar Nasser on 19/04/2020.
**/


#pragma once

#include <list>
#include <string>

#include <SFML/Graphics/Drawable.hpp>

#include <NasNas/core/data/Rect.hpp>
#include <NasNas/core/Layer.hpp>

namespace ns {
    class Camera;

    class Scene : public sf::Drawable {
        friend class App;
        friend Camera;
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
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = default;

        template <typename... T>
        void createLayers(const T&... name) {
            (m_layers.emplace_back(name), ...);
        }

        /**
         * \brief Removes and clears the Layer of the given name
         *
         * \param name Layer name to remove
         */
        void deleteLayer(const std::string& name);

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
        std::string m_name;         ///< Scene name
        std::list<Layer> m_layers;
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
    };

}
