/**
* Created by Modar Nasser on 26/08/2020.
**/

#pragma once

#include <functional>
#include <vector>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include <NasNas/core/AppAccess.hpp>

namespace ns {

    class Transition : public sf::Drawable {
        friend class App;
    public:
        void onEnd(const std::function<void()>& fn);

    protected:
        Transition();
        void addShape(const sf::Shape& shape);
        void end();
        virtual void onUpdate() = 0;

    private:
        void start();

        auto hasStarted() const -> bool;
        auto hasEnded() const -> bool;
        void update();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool m_started = false;
        bool m_ended = false;
        std::vector<const sf::Drawable*> m_drawables;
        std::function<void()> m_end_callback;

        sf::RenderTexture m_render_texture;
    };

    namespace transition {
        class CircleOpen : public Transition, public AppAccess<> {
        public:
            explicit CircleOpen(int duration_ms=1000);
            void setDuration(int duration_ms);
            void onUpdate() override;
        private:
            int m_duration_ms;
            float m_limit;
            float m_scale_factor;
            sf::CircleShape m_circle;
            sf::RectangleShape m_rectangle;
        };

        class CircleClose : public Transition, public AppAccess<> {
        public:
            explicit CircleClose(int duration_ms=1000);
            void setDuration(int duration_ms);
            void onUpdate() override;
        private:
            int m_duration_ms;
            float m_scale_factor;
            sf::CircleShape m_circle;
            sf::RectangleShape m_rectangle;
        };
    }


}
