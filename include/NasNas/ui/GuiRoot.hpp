// Created by Modar Nasser on 02/11/2021.

#pragma once

#include <SFML/System/Vector2.hpp>

#include <NasNas/core/AppAccess.hpp>
#include <NasNas/ui/Container.hpp>

namespace ns {
    class Camera;
}

namespace ns::ui {

    class GuiRoot : public Container, public AppAccess<> {
    public:
        GuiRoot();
        void setCamera(Camera& cam);
        auto getMousePosition() const -> sf::Vector2f;
        auto getTouchPosition(unsigned finger) const -> sf::Vector2f;

        void setMaxFingersCount(int finger_count);
        auto getMaxFingersCount() const -> int;

    private:
        using Container::setSize;
        Camera* m_cam = nullptr;
        int m_max_finger_count = 1;
    };

}
