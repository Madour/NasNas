/**
* Created by Modar Nasser on 20/04/2020.
**/


#pragma once

#include "NasNas/data/Rect.hpp"
#include "NasNas/data/ShaderHolder.hpp"
#include "NasNas/core/Scene.hpp"

namespace ns {

    class AppWindow;

    class Camera : public sf::View, public ShaderHolder {
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
        void reset(const ns::FloatRect& rectangle) ;

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
        void follow(Drawable& entity);

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

        /**
         * \brief Sets Camera move limits
         *
         * \param rectangle Limits rectangle
         */
        void setLimitsRectangle(const ns::IntRect& rectangle);

        /**
         * \brief Get Camera position in world's coordinates
         *
         * \return Camera position
         */
        auto getPosition() const -> sf::Vector2f;

        /**
         * \brief Get Camera left position in world's coordinates
         *
         * \return Camera left boundary position
         */
        auto getLeft() const -> float;

        /**
         * \brief Set Camera left position in world's coordinates
         *
         * \param value New left boundary position
         */
        void setLeft(float value);

        /**
         * \brief Get Camera right position in world's coordinates
         *
         * \return Camera right boundary position
         */
        auto getRight() const -> float;

        /**
         * \brief Set Camera right position in world's coordinates
         *
         * \param value New right boundary position
         */
        void setRight(float value);

        /**
         * \brief Get Camera top position in world's coordinates
         *
         * \return Camera top boundary position
         */
        auto getTop() const -> float;

        /**
         * \brief Set Camera top position in world's coordinates
         *
         * \param value New top boundary position
         */
        void setTop(float value);

        /**
         * \brief Get Camera bottom position in world's coordinates
         *
         * \return Camera bottom boundary position
         */
        auto getBottom() const -> float;

        /**
         * \brief Set Camera bottom position in world's coordinates
         *
         * \param value New bottom boundary position
         */
        void setBottom(float value);

        /**
         * \brief Get camera global bounds
         *
         * \return Camera rectangle view
         */
        auto getGlobalBounds() const -> ns::FloatRect;

        /**
         * \brief Updates Camera position if following an entity
         */
        void update();

    private:
        friend App;

        std::string m_name;                 ///< Camera name
        int m_render_order;                 ///< Camera render order
        bool m_visible;                     ///< Is the Camera content visible ?
        Scene* m_scene;                     ///< Scene looked at (content of the Camera)

        Drawable* m_reference;              ///< Entity followed by the Camera
        unsigned int m_frames_delay;        ///< Delay when following an entity

        ns::IntRect m_base_view;            ///< Camera size on creation or on reset
        ns::FloatRect m_base_viewport;      ///< Viewport size on creation or on viewport reset
        ns::IntRect m_limits = {0, 0, 0, 0};///< Camera move limits

        sf::RenderTexture m_render_texture; ///< Render texture where the view will be drawn
        sf::Sprite m_sprite;                ///< Sprite containing the render_texture's texture

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
