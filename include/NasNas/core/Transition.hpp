/**
* Created by Modar Nasser on 26/08/2020.
**/

#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "NasNas/data/Maths.hpp"
#include "NasNas/data/AppComponent.hpp"

namespace ns {

    class Transition : public AppComponent, public sf::Drawable {
    public:
        static std::vector<Transition*> list;

        Transition();
        void start();
        void end();

        auto hasStarted() const -> bool;
        auto hasEnded() const -> bool;

        void addShape(const sf::Shape& shape);

        void setOnEndCallback(const std::function<void()>& fn);

        void update();

    protected:
        virtual void onUpdate() = 0;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        bool m_started = false;
        bool m_ended = false;
        std::vector<const sf::Drawable*> m_drawables;
        std::function<void()> m_end_callback;

        sf::RenderTexture m_render_texture;
    };

    namespace transition {
        class CircleOpen : public Transition {
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

        class CircleClose : public Transition {
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
