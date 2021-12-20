// Created by Modar Nasser on 02/11/2021.


#include <NasNas/core/App.hpp>
#include <NasNas/ui/GuiRoot.hpp>

using namespace ns;
using namespace ns::ui;

GuiRoot::GuiRoot() {
    m_root = this;
}

void GuiRoot::setCamera(Camera& cam) {
    m_cam = &cam;
    setSize(cam.getSize().x, cam.getSize().y);
}

auto GuiRoot::getMousePosition() const -> sf::Vector2f {
    return app().getMousePosition(*m_cam);
}

auto GuiRoot::getTouchPosition(unsigned finger) const -> sf::Vector2f {
    return app().getTouchPosition(finger, *m_cam);
}

void GuiRoot::setMaxFingersCount(int finger_count) {
    m_max_finger_count = std::clamp(finger_count, 1, 10);
}

auto GuiRoot::getMaxFingersCount() const -> int {
    return m_max_finger_count;
}