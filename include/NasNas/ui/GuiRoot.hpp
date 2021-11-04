// Created by Modar Nasser on 02/11/2021.

#pragma once

#include <NasNas/core/Camera.hpp>
#include <NasNas/ui/Container.hpp>

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
