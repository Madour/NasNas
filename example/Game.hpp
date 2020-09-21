/**
* Created by Modar Nasser on 26/04/2020.
**/

#pragma once


#include "../NasNas.h"

class Game: public ns::App {
public:
    Game();
    ~Game() override;

    void onEvent(const sf::Event& event) override ;
    void update() override ;

private:
    ns::Scene* scene;
    ns::Camera* game_camera;

    ns::BitmapFont* font;

    ns::tm::TiledMap tiled_map;

    std::shared_ptr<ns::BaseEntity> player;
    std::shared_ptr<ns::ui::TypedText> textbox;

    std::vector<std::shared_ptr<ns::BaseEntity>> entities;
    std::vector<std::shared_ptr<sf::Shape>> shapes;

    sf::Shader* black_white_shader;
    sf::Shader* palette_shader;
    int frame_counter = 0;
};
