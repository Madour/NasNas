/**
* Created by Modar Nasser on 26/08/2020.
**/

#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "NasNas/core/Window.hpp"

namespace ns {

    class Transition : public sf::Drawable {
    public:
        static std::vector<std::unique_ptr<Transition>> list;

        explicit Transition(AppWindow& window);
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

        AppWindow* m_window;
        sf::RenderTexture m_render_texture;
    };

    class CircleOpenTransition : public Transition {
    public:
        explicit CircleOpenTransition(AppWindow& window);
        void onUpdate() override;
    private:
        sf::CircleShape m_circle;
    };

}
