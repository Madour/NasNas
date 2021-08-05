/**
* Created by Modar Nasser on 23/06/2020.
**/


#include <iostream>
#include "NasNas/core/data/Config.hpp"
#include "NasNas/core/App.hpp"

using namespace ns;

Config::debug_info::debug_info() :
utils::bool_switch([this]{
    show_fps = (m_state >> 0u) & 1u;
    show_text = (m_state >> 1u) & 1u;
    show_bounds = (m_state >> 2u) & 1u;
}, []{
    if (app) app->getWindow().setTitle(app->getTitle());
}),
show_fps([&]{m_state |= 1u<<0u;}, [&]{m_state &= ~(1u<<0u); if (app) app->getWindow().setTitle(app->getTitle());}),
show_text([&]{m_state |= 1u<<1u;}, [&]{m_state &= ~(1u<<1u);}),
show_bounds([&]{m_state |= 1u<<2u;}, [&]{m_state &= ~(1u<<2u);}),
m_state(7u)
{show_fps = show_text = show_bounds = true;}

auto Config::debug_info::operator=(bool value) -> debug_info& {
    value ? m_on_true() : m_on_false();
    m_val = value;
    return *this;;
}

Config::debug_info Config::debug;

const bool Config::Modules::Core = true;
const bool Config::Modules::Reslib =
#ifdef NS_RESLIB
        true;
#else
        false;
#endif

const bool Config::Modules::Ecs =
#ifdef NS_ECS
        true;
#else
        false;
#endif

const bool Config::Modules::Tilemapping =
#ifdef NS_TILEMAPPING
        true;
#else
        false;
#endif

const bool Config::Modules::Ui =
#ifdef NS_UI
        true;
#else
        false;
#endif

std::string Config::Window::title = "NasNas demo app";
sf::Vector2i Config::Window::size = {720, 480};
sf::Vector2i Config::Window::view_size = {0, 0};
int Config::Window::style = sf::Style::Default;
unsigned Config::Window::antialiasing = 0;
int Config::Window::framerate_limit = 60;
int Config::Window::update_rate = 60;
bool Config::Window::vertical_sync = false;
bool Config::Window::key_repeat = false;
bool Config::Window::cursor_visible = true;
bool Config::Window::cursor_grabbed = false;


float Config::Physics::gravity = 0;
