// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "NasNas/core/data/ShaderHolder.hpp"
#include "NasNas/core/graphics/Renderable.hpp"
#include "NasNas/core/Camera.hpp"
#include "NasNas/core/AppAccess.hpp"
#include "NasNas/ui/Widget.hpp"

namespace ns::ui {
class Container : public sf::Drawable, public sf::Transformable, public Renderable, public ShaderHolder, public AppAccess<> {
    public:
        sf::RenderTexture m_render_texture;
        std::vector<Widget*> m_widgets;
        ns::Camera* m_cam;

        void onEvent(const sf::Event& event);
        void setCamera(ns::Camera& cam);
        void render() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}
