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
    class Container : public sf::Drawable, public sf::Transformable, public Renderable, public ShaderHolder, public AppAccess<> {
    public:
        template <typename T>
        auto addWidget() -> T&;

        auto getSize() const -> sf::Vector2f;

        void setCamera(Camera& cam);

        void onEvent(const sf::Event& event);
        void render() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::RenderTexture m_render_texture;
        std::vector<std::shared_ptr<Widget>> m_widgets;
        Widget* m_hovered_widget = nullptr;
        Camera* m_cam = nullptr;
    };

    template <typename T>
    auto Container::addWidget() -> T& {
        auto* new_widget = new T();
        m_widgets.emplace_back(new_widget);
        return *new_widget;
    }
}
