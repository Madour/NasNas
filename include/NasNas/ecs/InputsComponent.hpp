/**
* Created by Modar Nasser on 24/06/2020.
**/


#pragma once

#include <functional>
#include <unordered_map>
#include <SFML/System.hpp>
#include "NasNas/data/Config.hpp"
#include "NasNas/ecs/BaseComponent.hpp"

namespace ns::ecs {

    class InputsComponent : public BaseComponent{
    public:
        explicit InputsComponent(BaseEntity* entity);

        void bind(sf::Keyboard::Key key, const std::function<void()>& function);

        void setCaptureInput(bool);

        void update() override;

    private:
        std::unordered_map<sf::Keyboard::Key, std::function<void()>> m_inputs;

        bool m_capture_input;
    };

}
