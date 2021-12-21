// Created by Modar Nasser on 04/08/2021.

#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SFML/Window/Keyboard.hpp>

#include <NasNas/core/data/Singleton.hpp>

namespace ns {
    class App;

    class Inputs :  public detail::Singleton<Inputs> {
        friend detail::Singleton<Inputs>;
        friend App;
    public:
        static auto getKeysDown() -> const std::vector<sf::Keyboard::Key>&;

        static auto isKeyDown(const sf::Keyboard::Key& key) -> bool;

        static auto isKeyPressed(const sf::Keyboard::Key& key) -> bool;
        static auto isKeyReleased(const sf::Keyboard::Key& key) -> bool;

        static void setButton(const std::string& btn, const sf::Keyboard::Key& key);
        static auto getButton(const std::string& btn) ->  sf::Keyboard::Key;

    private:
        Inputs() = default;
        using detail::Singleton<Inputs>::get;
        static void init();

        std::vector<sf::Keyboard::Key> m_keys_down;
        std::unordered_map<sf::Keyboard::Key, bool> m_keys_states;
        std::unordered_map<sf::Keyboard::Key, bool> m_keys_pressed;
        std::unordered_map<sf::Keyboard::Key, bool> m_keys_released;
        std::unordered_map<std::string, sf::Keyboard::Key> m_buttons_map;
    };
}
