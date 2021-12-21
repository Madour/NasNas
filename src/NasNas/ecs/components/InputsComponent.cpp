// Created by Modar Nasser on 17/08/2021.

#include <NasNas/ecs/components/InputsComponent.hpp>

#include <NasNas/core/Inputs.hpp>

using namespace ns;
using namespace ns::ecs;

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

void InputsComponent::enable() {
    m_enabled = true;
}

void InputsComponent::disable() {
    m_enabled = false;
}

void InputsComponent::update() {
    if (m_enabled) {
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
