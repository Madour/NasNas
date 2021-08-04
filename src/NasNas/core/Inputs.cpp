// Created by Modar Nasser on 04/08/2021.

#include "NasNas/core/Inputs.hpp"

void ns::Inputs::init() {
    get().m_keys_down.reserve(sf::Keyboard::KeyCount);
}

auto ns::Inputs::getKeysDown() -> const std::vector<sf::Keyboard::Key>& {
    return get().m_keys_down;
}

auto ns::Inputs::isKeyDown(const sf::Keyboard::Key& key) -> bool {
    auto& keys_states = get().m_keys_states;
    return keys_states.find(key) != keys_states.end() && keys_states.at(key);
}

auto ns::Inputs::isKeyPressed(const sf::Keyboard::Key& key) -> bool {
    auto& keys_pressed = get().m_keys_pressed;
    return keys_pressed.find(key) != keys_pressed.end();
}

auto ns::Inputs::isKeyReleased(const sf::Keyboard::Key& key) -> bool {
    auto& keys_released = get().m_keys_released;
    return keys_released.find(key) != keys_released.end();
}
