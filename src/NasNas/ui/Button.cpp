// Created by Modar Nasser on 10/10/2021.

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <NasNas/ui/Button.hpp>

using namespace ns::ui;

Button::Button() {
    setTextAlign(TextAlign::Center);
}

void Button::setTextAlign(TextAlign alignement) {
    switch (alignement) {
        case TextAlign::Left:
            text.setOrigin(0, text.getLocalBounds().height/2+5);
            text.setPosition(m_style.padding.left - m_style.clickable_zone.width/2, text.getPosition().y);
            break;
        case TextAlign::Center:
            text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2+5);
            text.setPosition(0, text.getPosition().y);
            break;
        case TextAlign::Right:
            text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height/2+5);
            text.setPosition(m_style.clickable_zone.width/2 - m_style.padding.right, text.getPosition().y);
            break;
    }
}

auto Button::getGlobalBounds() const -> sf::FloatRect {
    return getTransform().transformRect(m_style.clickable_zone);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    if (isFocused() && m_style.drawable_focused != nullptr)
        target.draw(*m_style.drawable_focused, states);
    else if (isHovered() && m_style.drawable_hovered != nullptr)
        target.draw(*m_style.drawable_hovered, states);
    else if (m_style.drawable != nullptr)
        target.draw(*m_style.drawable, states);

    target.draw(text, states);
}
