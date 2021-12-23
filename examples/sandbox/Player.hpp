/**
* Created by Modar Nasser on 07/06/2020.
**/

#pragma once

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Ecs.hpp>
#include <cmath>

class Player : public ns::EntityObject, public sf::Drawable {
public:
    Player();
    void update();

    void moveForward();
    void moveBackward();
    void turnRight();
    void turnLeft();

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    auto getPosition() const -> sf::Vector2f;
    auto getGlobalBounds() const -> ns::FloatRect;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ns::Spritesheet m_spritesheet;
    float m_rotation = 0.0;
};

