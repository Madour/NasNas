// Created by Modar Nasser on 04/08/2021.

#include "NasNas/core/Inputs.hpp"

using namespace ns;

void Inputs::init() {
    get().m_keys_down.reserve(sf::Keyboard::KeyCount);
}

auto Inputs::getKeysDown() -> const std::vector<sf::Keyboard::Key>& {
    return get().m_keys_down;
}

auto Inputs::isKeyDown(const sf::Keyboard::Key& key) -> bool {
    auto& keys_states = get().m_keys_states;
    return keys_states.find(key) != keys_states.end() && keys_states.at(key);
}

auto Inputs::isKeyPressed(const sf::Keyboard::Key& key) -> bool {
    auto& keys_pressed = get().m_keys_pressed;
    return keys_pressed.find(key) != keys_pressed.end();
}

auto Inputs::isKeyReleased(const sf::Keyboard::Key& key) -> bool {
    auto& keys_released = get().m_keys_released;
    return keys_released.find(key) != keys_released.end();
}

void Inputs::setButton(const std::string& btn, const sf::Keyboard::Key& key) {
    get().m_buttons_map[btn] = key;
}

auto Inputs::getButton(const std::string& btn) -> sf::Keyboard::Key {
    auto& btns_map = get().m_buttons_map;
    if (btns_map.find(btn) != btns_map.end())
        return btns_map.at(btn);
    return sf::Keyboard::Unknown;
}
