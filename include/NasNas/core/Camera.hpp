/**
* Created by Modar Nasser on 20/04/2020.
**/

#pragma once

#include "NasNas/data/AppComponent.hpp"
#include "NasNas/data/Rect.hpp"
#include "NasNas/core/Scene.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

namespace ns {

    class AppWindow;

    class Camera: public sf::View {
    public:
        /**
         * \brief Construct a Camera object
         *
         * \param name Name of the Camera object
         * \param render_order Render order of the Camera object
         */
        Camera(const std::string& name, int render_order);

        void setName(const std::string& name);

        /**
         * \brief Reset Camera size and position
         *
         * \param position New position
         * \param size New size
         */
        void reset(sf::Vector2i position, sf::Vector2i size);

        /**
         * \brief Reset Camera size and position
         *
         * \param x New X position
         * \param y New Y position
         * \param w New width
         * \param h New height
         */
        void reset(int x, int y, int w, int h);

        /**
         * \brief Reset Camera size and position
         *
         * \param rectangle New rectangle {position, size}
         */
        void reset(const FloatRect& rectangle) ;

        /**
         * \brief Reset Camera viewport
         *
         * Viewport defines how much space Camera content should take on the window
         * and where it is placed. Coordinates in percentage.
         * e.g. :
         * 0 = 0% of the window
         * 0.5 = 50% of the window
         * 1 = 100% of the window
         *
         * \param position New viewport position
         * \param size New viewport size
         */
        void resetViewport(sf::Vector2f position, sf::Vector2f size);

        /**
         * \brief Reset Camera viewport
         *
         * Viewport defines how much space Camera content should take on the window
         * and where it is placed. Coordinates in percentage.
         * e.g. :
         * 0 = 0% of the window
         * 0.5 = 50% of the window
         * 1 = 100% of the window
         *
         * \param x New viewport X pos
         * \param y New viewport Y pos
         * \param w New viewport width
         * \param h New viewport height
         */
        void resetViewport(float x, float y, float w, float h);

        /**
         * \brief Is the Camera looking at a Scene ?
         *
         * \return True if Camera looking at a Scene
         */
        auto hasScene() -> bool;

        /**
         * \brief Get the Scene looked at
         *
         * \return Scene object reference
         */
        auto getScene() -> Scene&;

        /**
         * \brief Tell the Camera to look at a Scene
         *
         * \param scene Pointer to a Scene object
         */
        void lookAt(Scene* scene);

        /**
         * \brief Is the Camera visible ?
         *
         * \return True if the Camera is visible
         */
        auto isVisible() const -> bool;
        /**
         * \brief Show or hide the Camera content
         *
         * \param value
         */
        void setVisible(bool value);

        /**
         * \brief Follow an entity, Camera position will be updated accordingly automatically.
         *
         * \param entity BaseEntity to be followed
         */
        void follow(BaseEntity& entity);

        /**
         * \brief Get render order of the Camera
         *
         * 0 is rendered first, then 1, then 2 ...
         *
         * \return Camera render order
         */
        auto getRenderOrder() const -> int;

        /**
         * \biref Get delay in position update over the followed entity
         *
         * \return Frame delay
         */
        auto getFramesDelay() const -> unsigned int;

        /**
         * \brief Set the frame delay
         *
         * A delay of N means the Camera will need N frames
         * to go to the followed entity position. Allows smooth camera movements
         *
         * \param value Frame delay
         */
        void setFramesDelay(unsigned int value);

        auto getPosition() const -> sf::Vector2f;

        auto getLeft() const -> float;
        void setLeft(float value);

        auto getRight() const -> float;
        void setRight(float value);

        auto getTop() const -> float;
        void setTop(float value);

        auto getBottom() const -> float;
        void setBottom(float value);

        auto getBounds() const -> FloatRect;

        /**
         * \brief Updates Camera position if following an entity
         */
        void update();

    private:
        friend AppWindow; friend App;

        std::string m_name;             ///< Camera name
        int m_render_order;             ///< Camera render order
        bool m_visible;                 ///< Is the Camera content visible ?
        Scene* m_scene;                 ///< Scene looked at (content of the Camera)

        BaseEntity* m_reference;        ///< Entity followed by the Camera
        unsigned int m_frames_delay;    ///< Delay when following an entity

        IntRect m_base_view;            ///< Camera size on creation or on reset
        FloatRect m_base_viewport;      ///< Viewport size on creation or on viewport reset

        sf::RenderTexture m_render_texture;
        sf::Sprite m_sprite;

        /**
         * \brief Camera default constructor
         */
        Camera();

        /**
         * \brief Renders Camera content on the given target
         * \param target Target where content is drawn on, usualy the AppWindow
         */
        void render(sf::RenderTarget& target);

    };

}
