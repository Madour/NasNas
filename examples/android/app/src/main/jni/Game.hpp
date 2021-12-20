/**
* Created by Modar Nasser on 26/04/2020.
**/

#pragma once

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Tilemapping.hpp>
#include <NasNas/Ecs.hpp>
#include <NasNas/Ui.hpp>

#include "Player.hpp"

class Game: public ns::App {
public:
    Game();
    void onEvent(const sf::Event& event) override ;
    void update() override ;

private:
    int m_frame_counter = 0;
    ns::tm::TiledMap m_tiled_map;
    sf::Transformable m_camera_anchor;
    Player m_player;

    ns::ui::GuiRoot m_gui;
    sf::CircleShape m_btn_drawable;
    sf::CircleShape m_btn_drawable_focused;
};
