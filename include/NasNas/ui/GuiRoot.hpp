// Created by Modar Nasser on 02/11/2021.

#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <NasNas/core/data/ShaderHolder.hpp>
#include <NasNas/core/graphics/Renderable.hpp>
#include <NasNas/core/Camera.hpp>
#include <NasNas/core/AppAccess.hpp>
#include <NasNas/ui/Container.hpp>
#include <NasNas/ui/Widget.hpp>

namespace ns::ui {
    class GuiRoot : public Container, public AppAccess<> {
    public:
        GuiRoot();
        void setCamera(Camera& cam);
        auto getMousePosition() const -> sf::Vector2f;

    private:
        using Container::setSize;
        Camera* m_cam = nullptr;
    };

}
