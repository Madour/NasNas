// Created by Modar Nasser on 10/10/2021.

#include "NasNas/ui/Container.hpp"
#include "NasNas/core/App.hpp"
#include "NasNas/core/data/Logger.hpp"

using namespace ns::ui;

void Container::onEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseMoved:
            {
                auto mouse_pos = app().getMousePosition(*m_cam);
                for (auto* widget : m_widgets) {
                    if (widget->getGlobalBounds().contains(mouse_pos)) {
                        widget->onHover();
                    }
                }
            }
            break;
        case sf::Event::TouchBegan:
            break;
        default:
            break;
    }
}

void Container::setCamera(ns::Camera& cam) {
    m_cam = &cam;
    m_render_texture.create(m_cam->getSize().x, m_cam->getSize().y);
}

void Container::render() {
    m_render_texture.clear(sf::Color::Transparent);
    for (auto* widget : m_widgets) {
        m_render_texture.draw(*widget);
    }
    m_render_texture.display();
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.shader = getShader();
    states.transform *= getTransform();
    target.draw(sf::Sprite(m_render_texture.getTexture()), states);
}
