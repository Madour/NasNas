
#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

#include "Game.hpp"

auto main() -> int {

    ns::Res::load("assets");
    ns::Res::printTree();

    //------------ Game Config ---------------------------------------
    // set input buttons
    ns::Inputs::setButton("left", sf::Keyboard::Left);
    ns::Inputs::setButton("right", sf::Keyboard::Right);
    ns::Inputs::setButton("up", sf::Keyboard::Up);
    ns::Inputs::setButton("down", sf::Keyboard::Down);
    ns::Inputs::setButton("fullscreen", sf::Keyboard::F);
    //-----------------------------------------------------------------

    Game game;
    game.run();

    ns::Res::dispose();

    return 0;
}
