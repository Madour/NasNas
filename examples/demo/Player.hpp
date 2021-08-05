/**
* Created by Modar Nasser on 07/06/2020.
**/

#pragma once

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Ecs.hpp>
#include <cmath>

class Player : public ns::BaseEntity {
public:
    Player();
    ~Player() override;
    void update() override;
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
private:
    ns::Spritesheet* m_spritesheet = nullptr;
    float m_rotation = 0.0;
};

