
#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

#include "Game.hpp"

auto main() -> int {
    ns::android::init();
    ns::android::setScreenOrientation(ns::android::ScreenOrientation::Landscape);
    ns::android::hideNavigation();
    ns::android::hideStatusBar();

    ns::Res::load("assets");

    //------------ Game Config ---------------------------------------
    // set input buttons
    ns::AppConfig config;
    config.vertical_sync = true;
    config.resolution = {600, 300};
    config.scale = 2;
    config.title = "NasNas Platformer demo";
    ns::Settings::setConfig(config);
    //-----------------------------------------------------------------

    Game game;
    game.run();

    ns::Res::dispose();

    return 0;
}
