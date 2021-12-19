// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <functional>

#include <SFML/Graphics/Text.hpp>

#include <NasNas/ui/Style.hpp>
#include <NasNas/ui/Widget.hpp>

namespace ns::ui {

    class Button : public StyledWidget<style::Button>, public ClickableWidget {
    public:
        Button();

        sf::Text text;

        void setTextAlign(TextAlign alignement);

        auto getGlobalBounds() const -> sf::FloatRect override;
        auto contains(const sf::Vector2f& pos) const -> bool override;

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };

}
