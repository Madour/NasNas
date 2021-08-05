
#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

#include "Game.hpp"

auto main() -> int {

    ns::Res::load("assets");
    ns::Res::printTree();

    //------------ Game Config ---------------------------------------
    // window config
    ns::Config::Window::vertical_sync = true;
    ns::Config::Window::style = sf::Style::Default;
    // map keys inputs
    ns::Inputs::setButton("left", sf::Keyboard::Left);
    ns::Inputs::setButton("right", sf::Keyboard::Right);
    ns::Inputs::setButton("up", sf::Keyboard::Up);
    ns::Inputs::setButton("down", sf::Keyboard::Down);
    ns::Inputs::setButton("fullscreen", sf::Keyboard::F);
    // configure physics constants
    ns::Config::Physics::gravity = 0;
    //-----------------------------------------------------------------

    Game game;
    game.run();

    ns::Res::dispose();

    return 0;
}
