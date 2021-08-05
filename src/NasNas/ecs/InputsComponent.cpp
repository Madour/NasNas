/**
* Created by Modar Nasser on 24/06/2020.
**/


#include "NasNas/core/Inputs.hpp"
#include "NasNas/ecs/InputsComponent.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;
using namespace ns::ecs;

InputsComponent::InputsComponent() :
m_capture_input(true)
{}

void InputsComponent::reset() {
    m_inputs.clear();
    m_onpress.clear();
    m_onrelease.clear();
}

void InputsComponent::bind(sf::Keyboard::Key key, const std::function<void()>& function) {
    m_inputs[key] = function;
}

void InputsComponent::onPress(sf::Keyboard::Key key, const std::function<void()>& function) {
    m_onpress[key] = function;
}

void InputsComponent::onRelease(sf::Keyboard::Key key, const std::function<void()>& function) {
    m_onrelease[key] = function;
}

void InputsComponent::setCaptureInput(bool capture_input) {
    m_capture_input = capture_input ;
}

void InputsComponent::update() {
    if (m_capture_input) {
        for (auto it = ns::Inputs::getKeysDown().begin(); it < ns::Inputs::getKeysDown().end(); ++it) {
            for (const auto& [key, fn] : m_inputs)
                if (key == *it)
                    fn();
        }

        for (const auto& [key, fn] : m_onpress) {
            if (ns::Inputs::isKeyPressed(key))
                fn();
        }

        for (const auto& [key, fn] : m_onrelease) {
            if (ns::Inputs::isKeyReleased(key))
                fn();
        }
    }

}
