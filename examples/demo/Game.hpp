/**
* Created by Modar Nasser on 26/04/2020.
**/

#pragma once

#include "NasNas.h"

#include "Player.hpp"
#include "ShaderTransition.hpp"

class Game: public ns::App {
public:
    Game();
    ~Game() override;

    void onEvent(const sf::Event& event) override ;
    void update() override ;

private:
    ns::BitmapFont* font;
    ns::ui::TypedText* textbox;

    ns::tm::TiledMap tiled_map;

    Player player;
    std::vector<sf::CircleShape> shapes;

    sf::Shader* palette_shader;
    int frame_counter = 0;
};
