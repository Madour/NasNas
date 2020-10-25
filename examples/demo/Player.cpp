/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player()
: ns::BaseEntity("Player") {
    // creating Player spritesheet and setting its animations

    // entering manual all frames
    /*m_spritesheet = new ns::Spritesheet(
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
    );*/
    // using a grid
    m_spritesheet = new ns::Spritesheet("adventurer", ns::Res::getTexture("adventurer.png"));
    m_spritesheet->setGrid({50, 37}, 7);
    m_spritesheet->addAnim("idle", 0, 4, 200, sf::Vector2i(25, 37));
    m_spritesheet->addAnim("walk", 8, 6, 150, sf::Vector2i(25, 37));
    // adding sprite component to player (from spritesheet defined above)
    addComponent<ns::ecs::SpriteComponent>(m_spritesheet);

    // adding physics component to player
    addComponent<ns::ecs::PhysicsComponent>(sf::Vector2f(0.5f, 0.5f),  5.f, sf::Vector2f(0.1f, 0.1f));

    // adding shape component to player (blue square)
    auto* shape_component = new ns::ecs::ConvexShapeComponent(this, 4, sf::Vector2f(0, -15));
    shape_component->getDrawable().setFillColor(sf::Color::Blue);
    shape_component->getDrawable().setPoint(0, {-5, -5});
    shape_component->getDrawable().setPoint(1, {5, -5});
    shape_component->getDrawable().setPoint(2, {5, 5});
    shape_component->getDrawable().setPoint(3, {-5, 5});
    addComponent(shape_component);

    // adding inputs component to player and binding buttons to Player methods
    addComponent<ns::ecs::InputsComponent>();
    inputs()->bind(ns::Config::Inputs::getButtonKey("left"), [&](){ moveLeft(); });
    inputs()->bind(ns::Config::Inputs::getButtonKey("right"), [&](){ moveRight(); });
    inputs()->bind(ns::Config::Inputs::getButtonKey("up"), [&](){ moveUp(); });
    inputs()->bind(ns::Config::Inputs::getButtonKey("down"), [&](){ moveDown(); });

    addComponent<ns::ecs::ColliderComponent>(new ns::ecs::RectangleCollision(15, 30), sf::Vector2f(0, -15));

}
Player::~Player() {
    delete(m_spritesheet);
}

void Player::moveLeft() {
    physics()->setDirectionX(-1);
    graphics<ns::ecs::SpriteComponent>(0)->getDrawable().setScale(-1, 1);
    graphics<ns::ecs::SpriteComponent>(0)->setAnimState("walk");
}
void Player::moveRight() {
    physics()->setDirectionX(1.f);
    graphics<ns::ecs::SpriteComponent>(0)->getDrawable().setScale(1, 1);
    graphics<ns::ecs::SpriteComponent>(0)->setAnimState("walk");
}
void Player::moveUp() {
    physics()->setDirectionY(-1.f);
}
void Player::moveDown() {
    physics()->setDirectionY(1.f);
}

void Player::update() {
    // reset physics direction
    physics()->setDirection(0, 0);

    // update Player inputs component
    inputs()->update();

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
