// Created by Modar Nasser on 10/10/2021.

#include <NasNas/core/App.hpp>
#include <NasNas/core/data/Logger.hpp>
#include <NasNas/ui/Container.hpp>

using namespace ns;
using namespace ns::ui;

void Container::onEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseMoved:
            {
                auto mouse_pos = app().getMousePosition(*m_cam);
                Widget* widget_hovered = nullptr;
                for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); it++) {
                    auto& widget = *it;
                    if (widget->getGlobalBounds().contains(mouse_pos)) {
                        widget_hovered = widget.get();
                        break;
                    }
                }
                if (m_hovered_widget && m_hovered_widget != widget_hovered) {
                    m_hovered_widget->m_hovered = false;
                    m_hovered_widget->m_focused = false;
                    m_hovered_widget->call(Callback::onUnhover);
                }
                m_hovered_widget = widget_hovered;
                if (m_hovered_widget && !m_hovered_widget->m_hovered) {
                    m_hovered_widget->m_hovered = true;
                    m_hovered_widget->call(Callback::onHover);
                }
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (m_hovered_widget != nullptr) {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    m_hovered_widget->call(Callback::onLeftClickPress);
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                    m_hovered_widget->call(Callback::onRightClickPress);
                else if (event.mouseButton.button == sf::Mouse::Button::Middle)
                    m_hovered_widget->call(Callback::onMiddleClickPress);
                m_hovered_widget->m_focused = true;
                m_hovered_widget->call(Callback::onFocus);
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (m_hovered_widget != nullptr) {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    m_hovered_widget->call(Callback::onLeftClickRelease);
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                    m_hovered_widget->call(Callback::onRightClickRelease);
                else if (event.mouseButton.button == sf::Mouse::Button::Middle)
                    m_hovered_widget->call(Callback::onMiddleClickRelease);
                m_hovered_widget->m_focused = false;
                m_hovered_widget->call(Callback::onUnfocus);
            }
            break;
        case sf::Event::TouchBegan:
            break;
        default:
            break;
    }
}

void Container::setCamera(Camera& cam) {
    m_cam = &cam;
    m_render_texture.create(m_cam->getSize().x, m_cam->getSize().y);
}

auto Container::getSize() const -> sf::Vector2f {
    return sf::Vector2f(m_render_texture.getSize());
}

void Container::render() {
    m_render_texture.clear(sf::Color::Transparent);
    for (auto& widget : m_widgets) {
        m_render_texture.draw(*widget);
    }
    m_render_texture.display();
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.shader = getShader();
    states.transform *= getTransform();
    target.draw(sf::Sprite(m_render_texture.getTexture()), states);
}
