// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <NasNas/core/data/ShaderHolder.hpp>
#include <NasNas/core/graphics/Renderable.hpp>
#include <NasNas/core/Camera.hpp>
#include <NasNas/core/AppAccess.hpp>
#include <NasNas/ui/Widget.hpp>

namespace ns::ui {
    class Container : public Widget, public Renderable, public ShaderHolder {
    public:
        using Widget::Widget;

        template <typename T>
        auto addWidget() -> T&;

        void setSize(float x, float y);
        auto getSize() const -> sf::Vector2f;
        auto getGlobalBounds() const -> sf::FloatRect override;

        void onEvent(const sf::Event& event);
        void render() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        auto getHoveredWidget() const -> Widget*;
        sf::RenderTexture m_render_texture;
        sf::Vector2f m_size;
        sf::View m_view;
        std::vector<std::shared_ptr<Widget>> m_widgets;
        Widget* m_hovered_widget = nullptr;
    };

    template <typename T>
    auto Container::addWidget() -> T& {
        auto* new_widget = new T();
        new_widget->m_root = m_root;
        new_widget->m_parent = this;
        m_widgets.emplace_back(new_widget);
        return *new_widget;
    }
}
