/**
* Created by Modar Nasser on 23/06/2020.
**/


#pragma once

#include <filesystem>
#include <unordered_map>
#include "SFML/Window.hpp"

namespace ns {

    class Config {
    public:
        static const std::filesystem::path base_path;
        static bool debug;

        class Window {
        public:
            static std::string title;
            static sf::Vector2i size;
            static sf::Vector2i view_size;
            static int style;
            static int framerate_limit;
            static int update_rate;
            static bool vertical_sync;
            static bool key_repeat;
            static bool cursor_visible;
            static bool cursor_grabbed;
        };

        class Inputs {
        public:
            static std::vector<sf::Keyboard::Key> pressed_keys;        ///< Vector of pressed keys
            static void setButtonKey(const std::string& btn_name, sf::Keyboard::Key key);
            static auto getButtonKey(const std::string& btn_name) -> sf::Keyboard::Key;
        private:
            static std::unordered_map<std::string, sf::Keyboard::Key> m_key_buttons_map;
        };

        class Physics {
        public:
            static float gravity;
        };
    };

}
