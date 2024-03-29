
#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

#include "Game.hpp"

auto main() -> int {

    ns::Res::load("assets");

    //------------ Game Config ---------------------------------------
    // set input buttons
    ns::Inputs::setButton("left", sf::Keyboard::Left);
    ns::Inputs::setButton("right", sf::Keyboard::Right);
    ns::Inputs::setButton("up", sf::Keyboard::Up);
    ns::Inputs::setButton("down", sf::Keyboard::Down);
    ns::Inputs::setButton("fullscreen", sf::Keyboard::F);

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
