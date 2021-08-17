// Created by Modar Nasser on 17/08/2021.

#pragma once

#include <functional>
#include <map>

#include <SFML/Window/Keyboard.hpp>

namespace ns::ecs {
    class InputsComponent {
    public:
        void reset();

        void bind(sf::Keyboard::Key key, const std::function<void()>& function);
        void onPress(sf::Keyboard::Key key, const std::function<void()>& function);
        void onRelease(sf::Keyboard::Key key, const std::function<void()>& function);

        void enable();
        void disable();

        void update();

    private:
        bool m_enabled = true;
        std::map<sf::Keyboard::Key, std::function<void()>> m_inputs;
        std::map<sf::Keyboard::Key, std::function<void()>> m_onpress;
        std::map<sf::Keyboard::Key, std::function<void()>> m_onrelease;
    };

}



