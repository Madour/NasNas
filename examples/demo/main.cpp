
#include "NasNas.h"

#include "Game.hpp"

auto main() -> int {

    ns::Res::load("assets");
    ns::Res::printTree();

    //------------ Game Config ---------------------------------------
    // window config
    ns::Config::Window::vertical_sync = true;
    ns::Config::Window::style = sf::Style::Default;
    // map keys inputs
    ns::Config::Inputs::setButtonKey("left", sf::Keyboard::Left);
    ns::Config::Inputs::setButtonKey("right", sf::Keyboard::Right);
    ns::Config::Inputs::setButtonKey("up", sf::Keyboard::Up);
    ns::Config::Inputs::setButtonKey("down", sf::Keyboard::Down);
    ns::Config::Inputs::setButtonKey("fullscreen", sf::Keyboard::F);
    // configure physics constants
    ns::Config::Physics::gravity = 0;
    //-----------------------------------------------------------------

    Game game;
    game.run();

    ns::Res::dispose();

    return 0;
}
