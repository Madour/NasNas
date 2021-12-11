// Created by Modar Nasser on 10/10/2021.

#include <NasNas/core/App.hpp>
#include <NasNas/ui/Container.hpp>
#include <NasNas/ui/GuiRoot.hpp>

#include <NasNas/core/data/Logger.hpp>

using namespace ns;
using namespace ns::ui;

Container::Container() {
    m_iscontainer = true;
    auto widget_default = m_default_callbacks.at(Callback::onUnhover);
    m_default_callbacks[Callback::onUnhover] = [this, widget_default] (Widget* w) {
        for (auto& widget : m_widgets) {
            widget->call(Callback::onUnhover);
        }
        widget_default(w);
    };
}

void Container::setSize(float x, float y) {
    m_size = {x, y};
    m_view.setSize(m_size - m_style.padding.topleft() - m_style.padding.bottomright());
    m_view.setViewport({m_style.padding.left / x, m_style.padding.top / y,
                        m_view.getSize().x / x, m_view.getSize().y / y});
    m_view.setCenter(m_view.getSize()/2.f);

    m_render_texture.create(x, y);
}

void Container::setSize(const sf::Vector2f& size) {
    setSize(size.x, size.y);
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
                    m_hovered_widget->call(Callback::onUnhover);
                }
                m_hovered_widget = widget_hovered;
                if (m_hovered_widget && !m_hovered_widget->m_hovered) {
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
                m_hovered_widget->call(Callback::onUnfocus);
            }
            break;
        case sf::Event::TouchBegan:
            break;
        default:
            break;
    }
    if (m_hovered_widget && m_hovered_widget->m_iscontainer) {
        dynamic_cast<Container*>(m_hovered_widget)->onEvent(event);
    }
}

void Container::render() {
    // if user did not call setSize, set minimum size to fit all child widgets
    if (!m_widgets.empty() && getSize() == sf::Vector2f(0, 0)) {
        sf::Vector2f max;
        for (auto& w : m_widgets) {
            auto gb = w->getGlobalBounds();
            max.x = std::max(max.x, gb.left + gb.width);
            max.y = std::max(max.y, gb.top + gb.height);
        }
        setSize(max + m_style.padding.topleft() + m_style.padding.bottomright());
    }

    m_render_texture.clear(sf::Color::Transparent);

    m_render_texture.setView(m_render_texture.getDefaultView());
    if (m_style.drawable != nullptr)
        m_render_texture.draw(*m_style.drawable);

    m_render_texture.setView(m_view);
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
    auto mouse_pos = m_root->getMousePosition();
    if (m_parent)
        mouse_pos = m_parent->getInverseTransform().transformPoint(mouse_pos);
    mouse_pos = getInverseTransform().transformPoint(mouse_pos);
    mouse_pos -= m_style.padding.topleft();
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
