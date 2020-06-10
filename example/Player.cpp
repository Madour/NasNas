/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player()
: ns::BaseEntity("Player") {

    m_spritesheet = new ns::Spritesheet(
        "adventurer",
        ns::Res::get().getTexture("adventurer"),
        {
            new ns::Anim("idle",
                {
                    ns::AnimFrame({0, 0, 50, 40}, 250),
                    ns::AnimFrame({50, 0, 50, 40}, 250)
                }
            )
        }
    );
    addComponent<ns::ecs::SpriteComponent>(this, m_spritesheet, "idle");
}
Player::~Player() {
    delete(m_spritesheet);
}

void Player::update() {
    ns::BaseEntity::update();
    setX(std::round(getX() + m_velocity.x));
    setY(std::round(getY() + m_velocity.y));
    //m_sprite.setPosition(getX(), getY());
    m_velocity = sf::Vector2f(m_velocity.x * 0.98, m_velocity.y * 0.98);
}