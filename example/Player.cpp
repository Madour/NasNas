/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player()
: ns::BaseEntity("Player") {
    // creating Player spritesheet and setting its animations
    m_spritesheet = new ns::Spritesheet(
        "adventurer",
        ns::Res::get().getTexture("adventurer"),
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
    auto shape_component = std::make_shared<ns::ecs::ShapeComponent<sf::ConvexShape>>(this, 3, sf::Vector2f(0, 0));
    shape_component->getDrawable().setFillColor(sf::Color::Red);
    shape_component->getDrawable().setOrigin(5, 0);
    shape_component->getDrawable().setPoint(0, {0, 0});
    shape_component->getDrawable().setPoint(1, {10, 0});
    shape_component->getDrawable().setPoint(2, {5, 10});
    addComponent<ns::ecs::ShapeComponent<sf::ConvexShape>>(shape_component);

    // adding inputs component to player and binding buttons to Player methods
    addComponent<ns::ecs::InputsComponent>(this);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("left"), &Player::moveLeft);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("right"), &Player::moveRight);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("up"), &Player::moveUp);
    inputs()->bind<Player>(ns::Config::Inputs::getButtonKey("down"), &Player::moveDown);

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
    // calling parent update
    ns::BaseEntity::update();
    // if Player is not moving (drection x == 0), set anim state to idle
    if (physics()->getDirection().x == 0)
        graphics<ns::ecs::SpriteComponent>(0)->setAnimState("idle");
}