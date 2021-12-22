// Created by Modar Nasser on 10/10/2021.

#include <NasNas/ui/Button.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace ns::ui;

Button::Button() {
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2+5);
    text.setPosition(0, text.getPosition().y);
}

void Button::setTextAlign(TextAlign alignement) {
    if (!style.region) return;
    auto region_bounds = style.region->getBounds();
    switch (alignement) {
        case TextAlign::Left:
            text.setOrigin(0, text.getLocalBounds().height/2+5);
            text.setPosition(style.padding.left - region_bounds.width/2, text.getPosition().y);
            break;
        case TextAlign::Center:
            text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2+5);
            text.setPosition(0, text.getPosition().y);
            break;
        case TextAlign::Right:
            text.setOrigin(text.getLocalBounds().width, text.getLocalBounds().height/2+5);
            text.setPosition(region_bounds.width/2 - style.padding.right, text.getPosition().y);
            break;
    }
}

auto Button::getGlobalBounds() const -> sf::FloatRect {
    return getTransform().transformRect(style.region->getBounds());
}

auto Button::contains(const sf::Vector2f& pos) const -> bool {
    if (!style.region) return false;
    return style.region->contains(getInverseTransform().transformPoint(pos));
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    if (isFocused() && style.drawable_focused != nullptr)
        target.draw(*style.drawable_focused, states);
    else if (isHovered() && style.drawable_hovered != nullptr)
        target.draw(*style.drawable_hovered, states);
    else if (style.drawable != nullptr)
        target.draw(*style.drawable, states);

    target.draw(text, states);
}
