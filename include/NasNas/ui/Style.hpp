// Created by Modar Nasser on 26/11/2021.

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Vector2.hpp>

namespace ns::ui {
    struct Style {
        sf::Vector2f padding_topleft;
        sf::Vector2f padding_botright;
        sf::Drawable* drawable = nullptr;
    };
}
