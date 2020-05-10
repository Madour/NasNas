
#include "NasNas.h"

#include "example/Game.hpp"

auto main() -> int {

    ns::Res::load("assets");
    ns::Res::printTree();
    Game game;
    game.run();

    return 0;
}


