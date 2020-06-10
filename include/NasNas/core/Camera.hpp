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
        friend AppWindow;
        Camera();
        Camera(const std::string& name, int render_order);

        void reset(sf::Vector2i position, sf::Vector2i size);
        void reset(int x, int y, int w, int h);
        void reset(const FloatRect& rectangle) ;

        void resetViewport(sf::Vector2f position, sf::Vector2f size);
        void resetViewport(float x, float y, float w, float h);

        auto hasScene() -> bool;
        auto getScene() -> Scene&;
        void lookAt(Scene* scene);

        void setVisible(bool value);
        auto isVisible() const -> bool;

        void follow(BaseEntity& entity);

        auto getRenderOrder() const -> int;

        auto getFramesDelay() const -> unsigned int;
        void setFramesDelay(unsigned int value);

        auto getPosition() const -> sf::Vector2f;

        auto getLeft() const -> double;
        void setLeft(float value);

        auto getRight() const -> double;
        void setRight(float value);

        auto getTop() const -> double;
        void setTop(float value);

        auto getBottom() const -> double;
        void setBottom(float value);

        auto getBounds() const -> FloatRect;

        void update();

    private:
        std::string m_name;
        int m_render_order;
        bool m_visible;
        BaseEntity* m_reference;
        unsigned int m_frames_delay;

        IntRect m_base_view;
        FloatRect m_base_viewport;

        Scene* m_scene;

    };

}
