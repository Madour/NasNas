/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player()
: ns::BaseEntity("Player") {
    // creating Player spritesheet and setting its animations
    m_spritesheet = new ns::Spritesheet(
        "adventurer",
        ns::Res::get().getTexture("adventurer.png"),
        {
            new ns::Anim("idle",
                {
                    ns::AnimFrame({0, 0, 50, 37}, 250, {25, 37}),
                    ns::AnimFrame({50, 0, 50, 37}, 200, {25, 37}),
                    ns::AnimFrame({100, 0, 50, 37}, 200, {25, 37}),
                    ns::AnimFrame({150, 0, 50, 37}, 250, {25, 37}),
                }
            ),
            new ns::Anim("walk",
                {
                    ns::AnimFrame({50, 37, 50, 37}, 150, {25, 37}),
                    ns::AnimFrame({100, 37, 50, 37}, 150, {25, 37}),
                    ns::AnimFrame({150, 37, 50, 37}, 150, {25, 37}),
                    ns::AnimFrame({200, 37, 50, 37}, 150, {25, 37}),
                    ns::AnimFrame({250, 37, 50, 37}, 150, {25, 37}),
                    ns::AnimFrame({300, 37, 50, 37}, 150, {25, 37}),
                }
            )
        }
    );
    // adding sprite component to player (from spritesheet defined above)
    addComponent<ns::ecs::SpriteComponent>(this, m_spritesheet, "idle");

    // adding physics component to player
    addComponent<ns::ecs::PhysicsComponent>(this, 1.f, sf::Vector2f(10, 10),sf::Vector2f(0.5f, 0.5f), sf::Vector2f(0.1f, 0.1f));

    // adding shape component to player (red triangle)
    auto shape_component = std::make_shared<ns::ecs::ShapeComponent<sf::ConvexShape>>(this, 4, sf::Vector2f(0, -15));
    shape_component->getDrawable().setFillColor(sf::Color::Blue);
    shape_component->getDrawable().setPoint(0, {-5, -5});
    shape_component->getDrawable().setPoint(1, {5, -5});
    shape_component->getDrawable().setPoint(2, {5, 5});
    shape_component->getDrawable().setPoint(3, {-5, 5});
    addComponent<ns::ecs::ShapeComponent<sf::ConvexShape>>(shape_component);

    // adding inputs component to player and binding buttons to Player methods
    addComponent<ns::ecs::InputsComponent>(this);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("left"), &Player::moveLeft);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("right"), &Player::moveRight);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("up"), &Player::moveUp);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("down"), &Player::moveDown);

    addComponent<ns::ecs::ColliderComponent>(this, new ns::ecs::RectangleCollision(15, 30), sf::Vector2f(-7, -30));

}
Player::~Player() {
    delete(m_spritesheet);
}

void Player::moveLeft() {
    physics()->setDirection(-1, physics()->getDirection().y);
    graphics<ns::ecs::SpriteComponent>(0)->getDrawable().setScale(-1, 1);
    graphics<ns::ecs::SpriteComponent>(0)->setAnimState("walk");
}
void Player::moveRight() {
    physics()->setDirection(1, physics()->getDirection().y);
    graphics<ns::ecs::SpriteComponent>(0)->getDrawable().setScale(1, 1);
    graphics<ns::ecs::SpriteComponent>(0)->setAnimState("walk");
}
void Player::moveUp() {
    physics()->setDirection(physics()->getDirection().x, -1);
}
void Player::moveDown() {
    physics()->setDirection(physics()->getDirection().x, 1);
}

void Player::update() {
    // reset physics direction
    physics()->setDirection(0, 0);

    // update Player inputs component
    inputs()->update<Player>();

    // updating physics component
    physics()->update();

    collider()->update();

    // updating graphics components
    for (const auto& graphic_comp: graphics()) {
        graphic_comp->update();
    }

    // moving and rotating the shape around the sprite
    auto& shape = graphics<ns::ecs::ShapeComponent<sf::ConvexShape>>(1)->getDrawable();

    m_rotation += 5;
    shape.setRotation(m_rotation);
    shape.move({ std::cos(ns::to_radian(m_rotation/2))*40, std::sin(ns::to_radian(m_rotation/2))*40 });

    // if Player is not moving (drection x == 0), set anim state to idle
    if (physics()->getDirection().x == 0)
        graphics<ns::ecs::SpriteComponent>(0)->setAnimState("idle");
}
