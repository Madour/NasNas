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
                    ns::AnimFrame({50, 40, 50, 40}, 150, {25, 40}),
                    ns::AnimFrame({100, 40, 50, 40}, 150, {25, 40}),
                    ns::AnimFrame({150, 40, 50, 40}, 150, {25, 40}),
                    ns::AnimFrame({200, 40, 50, 40}, 150, {25, 40}),
                    ns::AnimFrame({250, 40, 50, 40}, 150, {25, 40}),
                    ns::AnimFrame({300, 40, 50, 40}, 150, {25, 40}),
                }
            )
        }
    );
    // adding sprite component to player (from spritesheet defined above)
    addComponent<ns::ecs::SpriteComponent>(this, m_spritesheet, "idle");

    // adding shape component to player (red triangle)
    auto* shape_comp = new ns::ecs::ShapeComponent<sf::ConvexShape>(this, 3, {0, 0});
    shape_comp->getDrawable().setFillColor(sf::Color::Red);
    shape_comp->getDrawable().setOrigin(5, 0);
    shape_comp->getDrawable().setPoint(0, {0, 0});
    shape_comp->getDrawable().setPoint(1, {10, 0});
    shape_comp->getDrawable().setPoint(2, {5, 10});
    addComponent<ns::ecs::ShapeComponent<sf::ConvexShape>>(shape_comp);
}
Player::~Player() {
    delete(m_spritesheet);
}

void Player::update() {
    ns::BaseEntity::update();
    setX(std::round(getX() + m_velocity.x));
    setY(std::round(getY() + m_velocity.y));
    m_velocity = sf::Vector2f(m_velocity.x * 0.98, m_velocity.y * 0.98);
}