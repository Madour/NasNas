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
            static int width;
            static int height;
            static int view_width;
            static int view_height;
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
