// Created by Modar Nasser on 10/10/2021.

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "NasNas/ui/Button.hpp"

using namespace ns::ui;


void ButtonBase::onHover() {
    if (m_is_hovered)
        return;
    m_is_hovered = true;
    m_onhover(*this);
}

void ButtonBase::setOnHoverCallback(decltype(m_onhover) cb) {
    m_onhover = cb;
}
