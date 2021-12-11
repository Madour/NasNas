// Created by Modar Nasser on 26/11/2021.

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

namespace ns::ui {
    struct Style {
    private:
        struct Padding {
            float left = 0.f;
            float top = 0.f;
            float right = 0.f;
            float bottom = 0.f;
            auto topleft() const -> sf::Vector2f { return {left, top}; }
            auto bottomright() const -> sf::Vector2f { return {right, bottom}; }
        };
    public:
        Padding padding{};
        sf::Drawable* drawable = nullptr;
    };
}
