/**
* Created by Modar Nasser on 23/06/2020.
**/

#include "NasNas/data/Config.hpp"

using namespace ns;

bool Config::debug = true;

std::string Config::Window::title;
int Config::Window::width = 960;
int Config::Window::height = 540;
int Config::Window::view_width = 0;
int Config::Window::view_height = 0;
int Config::Window::style = sf::Style::Default;
int Config::Window::framerate_limit = 60;
int Config::Window::update_rate = 60;
bool Config::Window::vertical_sync = false;
bool Config::Window::key_repeat = false;
bool Config::Window::cursor_visible = true;
bool Config::Window::cursor_grabbed = false;