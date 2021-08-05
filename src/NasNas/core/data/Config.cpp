/**
* Created by Modar Nasser on 23/06/2020.
**/


#include "NasNas/core/data/Config.hpp"
#include "NasNas/core/App.hpp"

using namespace ns;

Settings::debug_info::debug_info() :
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

auto Settings::debug_info::operator=(bool value) -> debug_info& {
    value ? m_on_true() : m_on_false();
    m_val = value;
    return *this;;
}

Settings::debug_info Settings::debug_mode;

AppConfig Settings::user_config;

auto AppConfig::getViewSize() const -> const sf::Vector2f& {
    return view_size;
}

auto AppConfig::getViewRatio() const -> float {
    return view_ratio;
}

void Settings::setConfig(AppConfig config) {
    if (AppComponent::app == nullptr) {
        Settings::user_config = std::move(config);
    }
    else {
        std::cerr << "(ns::Settings::setConfig) Cannot set App configuration after App was run." << std::endl;
    }
}

auto Settings::getConfig() -> const AppConfig& {
    return user_config;
}

const bool Settings::Modules::Core = true;
const bool Settings::Modules::Reslib =
#ifdef NS_RESLIB
        true;
#else
        false;
#endif

const bool Settings::Modules::Ecs =
#ifdef NS_ECS
        true;
#else
        false;
#endif

const bool Settings::Modules::Tilemapping =
#ifdef NS_TILEMAPPING
        true;
#else
        false;
#endif

const bool Settings::Modules::Ui =
#ifdef NS_UI
        true;
#else
        false;
#endif
