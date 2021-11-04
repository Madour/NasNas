// Created by Modar Nasser on 10/10/2021.

#include <NasNas/core/App.hpp>
#include <NasNas/ui/Container.hpp>
#include <NasNas/ui/GuiRoot.hpp>

#include <NasNas/core/data/Logger.hpp>

using namespace ns;
using namespace ns::ui;

Container::Container() {
    m_iscontainer = true;
}

void Container::setSize(float x, float y) {
    m_size = {x, y};
    m_view.setSize(m_size);

    m_render_texture.create(x, y);
}

auto Container::getSize() const -> sf::Vector2f {
    return m_size;
}

auto Container::getGlobalBounds() const -> sf::FloatRect {
    return {getPosition(), getSize()};
}

void Container::onEvent(const sf::Event& event) {
    switch (event.type) {
        case sf::Event::MouseMoved:
        {
            auto* widget_hovered = getHoveredWidget();
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
    if (m_hovered_widget && m_hovered_widget->m_iscontainer)
        dynamic_cast<Container*>(m_hovered_widget)->onEvent(event);
}

void Container::render() {
    m_view.setCenter(getSize()/2.f);
    m_render_texture.setView(m_view);

    m_render_texture.clear(m_root == this ? sf::Color::Transparent : sf::Color::Blue);
    for (auto& widget : m_widgets)
        m_render_texture.draw(*widget);
    m_render_texture.display();
}

void Container::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.shader = getShader();
    states.transform *= getTransform();
    target.draw(sf::Sprite(m_render_texture.getTexture()), states);
}

auto Container::getHoveredWidget() const -> Widget* {
    auto mouse_pos = getInverseTransform().transformPoint(m_root->getMousePosition());
    Widget* widget_hovered = nullptr;
    for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); it++) {
        auto* widget = it->get();
        if (widget->getGlobalBounds().contains(mouse_pos)) {
            widget_hovered = widget;
            break;
        }
    }
    return widget_hovered;
}
