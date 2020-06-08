/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player()
: ns::BaseEntity("Player") {
    m_ns_sprite = new ns::Sprite(
        "toto",
        ns::Res::get().getTexture("adventurer"),
        {
            {"idle", ns::Anim(
                    {
                        ns::AnimFrame({0, 0, 50, 40}, 250),
                        ns::AnimFrame({50, 0, 50, 40}, 250)
                    }
                )
            }
        }
    );
    setSprite(m_ns_sprite);
}
Player::~Player() {
    delete(m_ns_sprite);
}

void Player::update() {
    ns::BaseEntity::update();
    setX(std::round(getX() + m_velocity.x));
    setY(std::round(getY() + m_velocity.y));
    m_sprite.setPosition(getX(), getY());
    m_velocity = sf::Vector2f(m_velocity.x * 0.98, m_velocity.y * 0.98);
}