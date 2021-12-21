// Created by Modar Nasser on 05/09/2021.

#pragma once

#include <SFML/Window/Event.hpp>

namespace ns {
    struct AppStateInterface {
        virtual void onEvent(const sf::Event&) {}
        virtual void update() {}
        virtual void preRender() {}
    };

    struct AppState : AppStateInterface {
        virtual ~AppState() = default;
    };
}
