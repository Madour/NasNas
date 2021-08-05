/**
* Created by Modar Nasser on 24/06/2020.
**/


#pragma once

#include <functional>
#include <unordered_map>
#include <SFML/System.hpp>
#include "NasNas/core/data/Config.hpp"
#include "NasNas/ecs/BaseComponent.hpp"

namespace ns::ecs {

    class InputsComponent : public Component<InputsComponent> {
    public:
        InputsComponent();

        void reset();

        void bind(sf::Keyboard::Key key, const std::function<void()>& function);
        void onPress(sf::Keyboard::Key key, const std::function<void()>& function);
        void onRelease(sf::Keyboard::Key key, const std::function<void()>& function);

        void setCaptureInput(bool);

        void update() override;

    private:
        bool m_capture_input;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> m_inputs;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> m_onpress;
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> m_onrelease;
    };

    typedef InputsComponent Inputs;
}
