/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <utility>
#include <algorithm>
#include <memory>
#include <filesystem>
#include <functional>

#include "SFML/Graphics.hpp"
#include "NasNas/data/Rect.hpp"


namespace ns {
    // forward declaration of App type
    class App;

    /** AppComponent
     * Allows any class to access App properties
     */
    class AppComponent {
    public:
        static App* app;
    };

    /** Drawable is an interface for any object
     * that is destined to be drawn on the window
     */
    class Drawable: public sf::Drawable {
    public:
        virtual auto getPosition() -> sf::Vector2f = 0;
        virtual auto getGlobalBounds() -> ns::FloatRect = 0;
        virtual void move(float offsetx, float offsety) = 0;
    };
}
