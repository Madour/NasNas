// Created by Modar Nasser on 10/10/2021.

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace ns::ui {
    class Widget : public sf::Drawable, public sf::Transformable {
    public:
        virtual auto getGlobalBounds() const -> sf::FloatRect = 0;
        virtual void onHover() {};
        virtual void onFocus() {};
        virtual void onClick() {};
    };
}
