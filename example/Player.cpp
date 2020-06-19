/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player()
: ns::BaseEntity("Player"){

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

    addComponent<ns::ecs::PhysicsComponent>(this, 10.f, sf::Vector2f(12, 12),sf::Vector2f(0.8, 0.8));

    // adding shape component to player (red triangle)
    auto shape_component = std::make_shared<ns::ecs::ShapeComponent<sf::ConvexShape>>(this, 3, sf::Vector2f(0, 0));
    shape_component->getDrawable().setFillColor(sf::Color::Red);
    shape_component->getDrawable().setOrigin(5, 0);
    shape_component->getDrawable().setPoint(0, {0, 0});
    shape_component->getDrawable().setPoint(1, {10, 0});
    shape_component->getDrawable().setPoint(2, {5, 10});
    addComponent<ns::ecs::ShapeComponent<sf::ConvexShape>>(shape_component);
}
Player::~Player() {
    delete(m_spritesheet);
}

auto Player::getDirection() -> sf::Vector2i {
    return physics()->getDirection();
}

void Player::update() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        physics()->setDirection(-1, 0);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        physics()->setDirection(1, 0);
    }
    else physics()->setDirection(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        physics()->setDirection(physics()->getDirection().x, -1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        physics()->setDirection(physics()->getDirection().x, 1);
    }
    else physics()->setDirection(physics()->getDirection().x, 0);

    ns::BaseEntity::update();
}