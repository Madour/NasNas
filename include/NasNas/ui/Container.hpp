// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <NasNas/core/data/ShaderHolder.hpp>
#include <NasNas/core/graphics/Renderable.hpp>
#include <NasNas/ui/Style.hpp>
#include <NasNas/ui/Widget.hpp>

namespace ns::ui {
    class Container : public StyledWidget<style::Basic>, public Renderable, public ShaderHolder {
    public:
        Container();

        template <typename T>
        auto addWidget() -> T&;

        void setSize(float x, float y);
        void setSize(const sf::Vector2f& size);
        auto getSize() const -> sf::Vector2f;

        auto getGlobalBounds() const -> sf::FloatRect override;
        auto contains(const sf::Vector2f& pos) const -> bool override;

        void onEvent(const sf::Event& event);
        void render() override;

    private:
        auto transformPosition(const sf::Vector2f& position) const -> sf::Vector2f;
        auto getWidgetUnder(const sf::Vector2f& position) const -> Widget*;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::vector<std::unique_ptr<Widget>> m_widgets;
        Widget* m_hovered_widget = nullptr;
        std::vector<Widget*> m_touched_widgets;

        sf::View m_view;
        sf::RenderTexture m_render_texture;
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
