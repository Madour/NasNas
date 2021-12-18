// Created by Modar Nasser on 10/10/2021.

#include <NasNas/core/App.hpp>
#include <NasNas/ui/Container.hpp>
#include <NasNas/ui/GuiRoot.hpp>

#include <NasNas/core/data/Logger.hpp>

using namespace ns;
using namespace ns::ui;

Container::Container() {
    m_type |= Type::Container;
    auto widget_default = m_default_callbacks.at(MouseCallback::onUnhover);
    m_default_callbacks[MouseCallback::onUnhover] = [this, widget_default] (Widget* w) {
        for (auto& widget : m_widgets) {
            if (widget->isHovered())
                widget->call(MouseCallback::onUnhover);
        }
        widget_default(w);
    };
}

void Container::setSize(float x, float y) {
    setSize({x, y});
}

void Container::setSize(const sf::Vector2f& size) {
    m_view.setSize(size - m_style.padding.topleft() - m_style.padding.bottomright());
    m_view.setViewport({m_style.padding.left / size.x, m_style.padding.top / size.y,
                        m_view.getSize().x / size.x, m_view.getSize().y / size.y});
    m_view.setCenter(m_view.getSize()/2.f);

    m_render_texture.create(unsigned(size.x), unsigned(size.y));
}

auto Container::getSize() const -> sf::Vector2f {
    return sf::Vector2f(m_render_texture.getSize());
}

auto Container::getGlobalBounds() const -> sf::FloatRect {
    return {getPosition(), getSize()};
}

void Container::onEvent(const sf::Event& event) {
    Widget* widget_hovered = nullptr;
    switch (event.type) {
        case sf::Event::MouseMoved:
            widget_hovered = getWidgetUnder(transformPosition(m_root->getMousePosition()));
            if (m_hovered_widget && m_hovered_widget != widget_hovered) {
                m_hovered_widget->call(MouseCallback::onUnhover);
            }
            m_hovered_widget = widget_hovered;
            if (m_hovered_widget && !m_hovered_widget->m_hovered) {
                m_hovered_widget->call(MouseCallback::onHover);
            }
            break;
        case sf::Event::MouseButtonPressed:
            if (m_hovered_widget != nullptr) {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    m_hovered_widget->call(ClickCallback::onLeftClickPress);
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                    m_hovered_widget->call(ClickCallback::onRightClickPress);
                else if (event.mouseButton.button == sf::Mouse::Button::Middle)
                    m_hovered_widget->call(ClickCallback::onMiddleClickPress);
                m_hovered_widget->call(MouseCallback::onFocus);
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (m_hovered_widget != nullptr) {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    m_hovered_widget->call(ClickCallback::onLeftClickRelease);
                else if (event.mouseButton.button == sf::Mouse::Button::Right)
                    m_hovered_widget->call(ClickCallback::onRightClickRelease);
                else if (event.mouseButton.button == sf::Mouse::Button::Middle)
                    m_hovered_widget->call(ClickCallback::onMiddleClickRelease);
                m_hovered_widget->call(MouseCallback::onUnfocus);
            }
            break;

        case sf::Event::TouchBegan:
            widget_hovered = getWidgetUnder(transformPosition(m_root->getTouchPosition(event.touch.finger)));
            if (m_hovered_widget && m_hovered_widget != widget_hovered) {
                m_hovered_widget->call(MouseCallback::onUnhover);
                m_hovered_widget->call(MouseCallback::onUnfocus);
            }
            m_hovered_widget = widget_hovered;
            if (m_hovered_widget && !m_hovered_widget->m_hovered) {
                m_hovered_widget->call(MouseCallback::onHover);
                m_hovered_widget->call(MouseCallback::onFocus);
            }
            break;

        case sf::Event::TouchMoved:
            widget_hovered = getWidgetUnder(transformPosition(m_root->getTouchPosition(event.touch.finger)));
            if (m_hovered_widget && m_hovered_widget != widget_hovered) {
                m_hovered_widget->call(MouseCallback::onUnhover);
            }
            m_hovered_widget = widget_hovered;
            if (m_hovered_widget && !m_hovered_widget->m_hovered) {
                m_hovered_widget->call(MouseCallback::onHover);
            }
            break;

        case sf::Event::TouchEnded:
            if (m_hovered_widget != nullptr) {
                m_hovered_widget->call(ClickCallback::onTouchEnded);
                m_hovered_widget->call(MouseCallback::onUnfocus);
                m_hovered_widget->call(MouseCallback::onUnhover);
                m_hovered_widget = nullptr;
            }
            break;

        default:
            break;
    }
    if (m_hovered_widget && (m_hovered_widget->m_type & Type::Container)) {
        dynamic_cast<Container*>(m_hovered_widget)->onEvent(event);
    }
}

void Container::render() {
    // if user did not call setSize, set minimum size to fit all child widgets
    if (!m_widgets.empty() && getSize() == sf::Vector2f(0, 0)) {
        sf::Vector2f max;
        for (auto& w : m_widgets) {
            auto bounds = w->getGlobalBounds();
            max.x = std::max(max.x, bounds.left + bounds.width);
            max.y = std::max(max.y, bounds.top + bounds.height);
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

auto Container::transformPosition(const sf::Vector2f& position) const -> sf::Vector2f {
    sf::Vector2f real_pos = position;
    if (m_parent)
        real_pos = m_parent->transformPosition(real_pos);
    real_pos = getInverseTransform().transformPoint(real_pos);
    real_pos -= m_style.padding.topleft();
    return real_pos;
}

auto Container::getWidgetUnder(const sf::Vector2f& position) const -> Widget* {
    Widget* widget_hovered = nullptr;
    for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); it++) {
        auto* widget = it->get();
        if (widget->getGlobalBounds().contains(position)) {
            widget_hovered = widget;
            break;
        }
    }
    return widget_hovered;
}

