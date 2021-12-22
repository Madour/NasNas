// Created by Modar Nasser on 10/10/2021.

#include <NasNas/ui/Container.hpp>

#include <NasNas/core/App.hpp>
#include <NasNas/ui/GuiRoot.hpp>

using namespace ns;
using namespace ns::ui;

Container::Container() {
    m_type |= Type::Parent;
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
    m_view.setSize(size - style.padding.topleft() - style.padding.bottomright());
    m_view.setViewport({style.padding.left / size.x, style.padding.top / size.y,
                        m_view.getSize().x / size.x, m_view.getSize().y / size.y});
    m_view.setCenter(m_view.getSize()/2.f);

    m_render_texture.create(unsigned(size.x), unsigned(size.y));

    if (m_touched_widgets.empty())
        m_touched_widgets.resize(m_root->getMaxFingersCount(), nullptr);
}

auto Container::getSize() const -> sf::Vector2f {
    return sf::Vector2f(m_render_texture.getSize());
}

auto Container::getGlobalBounds() const -> sf::FloatRect {
    return getTransform().transformRect({{0.f, 0.f}, getSize()});
}

auto Container::contains(const sf::Vector2f& pos) const -> bool {
    return getGlobalBounds().contains(pos);
}

void Container::onEvent(const sf::Event& event) {
    Widget* widget_hovered = nullptr;
    Widget* widget_touched = nullptr;
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
            if (event.touch.finger >= m_root->getMaxFingersCount()) break;
            widget_touched = getWidgetUnder(transformPosition(m_root->getTouchPosition(event.touch.finger)));
            if (m_touched_widgets[event.touch.finger] && m_touched_widgets[event.touch.finger] != widget_touched) {
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onUnhover);
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onUnfocus);
            }
            m_touched_widgets[event.touch.finger] = widget_touched;
            if (m_touched_widgets[event.touch.finger] && !m_touched_widgets[event.touch.finger]->m_hovered) {
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onHover);
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onFocus);
                m_touched_widgets[event.touch.finger]->call(ClickCallback::onTouchBegan);
            }
            break;

        case sf::Event::TouchMoved:
            if (event.touch.finger >= m_root->getMaxFingersCount()) break;
            widget_touched = getWidgetUnder(transformPosition(m_root->getTouchPosition(event.touch.finger)));
            if (m_touched_widgets[event.touch.finger] && m_touched_widgets[event.touch.finger] != widget_touched) {
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onUnhover);
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onUnfocus);
            }
            m_touched_widgets[event.touch.finger] = widget_touched;
            if (m_touched_widgets[event.touch.finger] && !m_touched_widgets[event.touch.finger]->m_hovered) {
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onHover);
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onFocus);
            }
            break;

        case sf::Event::TouchEnded:
            if (event.touch.finger >= m_root->getMaxFingersCount()) break;
            if (m_touched_widgets[event.touch.finger] != nullptr) {
                m_touched_widgets[event.touch.finger]->call(ClickCallback::onTouchEnded);
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onUnfocus);
                m_touched_widgets[event.touch.finger]->call(MouseCallback::onUnhover);
                m_touched_widgets[event.touch.finger] = nullptr;
            }
            break;

        default:
            break;
    }
    if (m_hovered_widget && (m_hovered_widget->m_type & Type::Parent)) {
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
        setSize(max + style.padding.topleft() + style.padding.bottomright());
    }

    m_render_texture.clear(sf::Color::Transparent);

    m_render_texture.setView(m_render_texture.getDefaultView());
    if (style.drawable != nullptr)
        m_render_texture.draw(*style.drawable);

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
    real_pos -= style.padding.topleft();
    return real_pos;
}

auto Container::getWidgetUnder(const sf::Vector2f& position) const -> Widget* {
    Widget* widget_hovered = nullptr;
    for (auto it = m_widgets.rbegin(); it != m_widgets.rend(); it++) {
        auto* widget = it->get();
        if (widget->contains(position)) {
            widget_hovered = widget;
            break;
        }
    }
    return widget_hovered;
}

