/**
* Created by Modar Nasser on 24/06/2020.
**/


#include "NasNas/ecs/InputsComponent.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;
using namespace ns::ecs;

const unsigned long Inputs::uid = BaseComponent::getNextId();

auto Inputs::getId() -> unsigned long {
    return Inputs::uid;
}

Inputs::Inputs(BaseEntity* entity) :
BaseComponent(entity),
m_capture_input(true)
{}

void Inputs::bind(sf::Keyboard::Key key, const std::function<void()>& function) {
    m_inputs[key] = function;
}

void Inputs::setCaptureInput(bool capture_input) {
    m_capture_input = capture_input ;
}

void Inputs::update() {
    if (m_capture_input)
        for (auto it = Config::Inputs::pressed_keys.rbegin(); it < Config::Inputs::pressed_keys.rend(); ++it)
            for (const auto& [key, fn] : m_inputs)
                if (key == *it)
                    fn();
}
