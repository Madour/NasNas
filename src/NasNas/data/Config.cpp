/**
* Created by Modar Nasser on 23/06/2020.
**/


#include <iostream>
#include "NasNas/data/Config.hpp"

using namespace ns;

bool Config::debug = false;

std::string Config::Window::title = "NasNas app";
sf::Vector2i Config::Window::size = {720, 480};
sf::Vector2i Config::Window::view_size = {0, 0};
int Config::Window::style = sf::Style::Default;
int Config::Window::framerate_limit = 60;
int Config::Window::update_rate = 60;
bool Config::Window::vertical_sync = false;
bool Config::Window::key_repeat = false;
bool Config::Window::cursor_visible = true;
bool Config::Window::cursor_grabbed = false;

std::vector<sf::Keyboard::Key> Config::Inputs::pressed_keys;
std::unordered_map<std::string, sf::Keyboard::Key> Config::Inputs::m_key_buttons_map;

void Config::Inputs::setButtonKey(const std::string& btn_name, sf::Keyboard::Key key) {
    m_key_buttons_map[btn_name] = key;
}

auto Config::Inputs::getButtonKey(const std::string& btn_name) -> sf::Keyboard::Key {
    if (m_key_buttons_map.count(btn_name) > 0)
        return m_key_buttons_map[btn_name];
    std::cout << "Error (Config::Inputs::getButtonKey) : No button named «" << btn_name
              << "» is defined in Config::Input. Please use Config::Input::setButtonKey first." << std::endl;
    exit(-1);
}

float Config::Physics::gravity = 0;
