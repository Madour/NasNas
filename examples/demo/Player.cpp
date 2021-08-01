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
    m_spritesheet->addAnim("idle", 0, 4, 200, {25, 37});
    m_spritesheet->addAnim("walk", 8, 6, 150, {25, 37});
    // adding sprite component to player (from spritesheet defined above)
    add<ns::ecs::Sprite>(m_spritesheet);

    // adding physics component to player
    add<ns::ecs::Physics>(sf::Vector2f(0.5f, 0.5f), 5.f, sf::Vector2f(0.1f, 0.1f));

    // adding shape component to player (blue square)
    auto convexshape = sf::ConvexShape(4);
    convexshape.setFillColor(sf::Color::Blue);
    convexshape.setPoint(0, {-5, -5});
    convexshape.setPoint(1, {5, -5});
    convexshape.setPoint(2, {5, 5});
    convexshape.setPoint(3, {-5, 5});
    add<ns::ecs::ConvexShape>(convexshape, sf::Vector2f(0, -15));

    auto velocity_vector = ns::LineShape();
    velocity_vector.setColor(sf::Color::Yellow);
    velocity_vector.addPoint(0, 0);
    velocity_vector.addPoint(1, 0, sf::Color::Red);
    add<ns::ecs::LineShape>(velocity_vector);

    // adding inputs component to player and binding buttons to Player methods
    add<ns::ecs::Inputs>();
    get<ns::ecs::Inputs>()->bind(ns::Config::Inputs::getButtonKey("left"), [&](){ moveLeft(); });
    get<ns::ecs::Inputs>()->bind(ns::Config::Inputs::getButtonKey("right"), [&](){ moveRight(); });
    get<ns::ecs::Inputs>()->bind(ns::Config::Inputs::getButtonKey("up"), [&](){ moveUp(); });
    get<ns::ecs::Inputs>()->bind(ns::Config::Inputs::getButtonKey("down"), [&](){ moveDown(); });

    add<ns::ecs::Collider>(new ns::ecs::RectangleCollision(15, 30), sf::Vector2f(0, -15));

}
Player::~Player() {
    delete(m_spritesheet);
}

void Player::moveLeft() {
    get<ns::ecs::Physics>()->setDirectionX(-1);
    get<ns::ecs::Sprite>()->getDrawable().setScale(-1, 1);
    get<ns::ecs::Sprite>()->setAnimState("walk");
}
void Player::moveRight() {
    get<ns::ecs::Physics>()->setDirectionX(1.f);
    get<ns::ecs::Sprite>()->getDrawable().setScale(1, 1);
    get<ns::ecs::Sprite>()->setAnimState("walk");
}
void Player::moveUp() {
    get<ns::ecs::Physics>()->setDirectionY(-1.f);
}
void Player::moveDown() {
    get<ns::ecs::Physics>()->setDirectionY(1.f);
}

void Player::update() {
    // reset physics direction
    get<ns::ecs::Physics>()->setDirection(0, 0);

    // update Player inputs component
    get<ns::ecs::Inputs>()->update();

    // updating physics component
    get<ns::ecs::Physics>()->update();

    get<ns::ecs::Collider>()->update();

    // updating graphics components
    get<ns::ecs::Sprite>()->update();

    // updating velocity vector
    auto& vel_vec = get<ns::ecs::LineShape>()->getDrawable();
    vel_vec.setPoint(1, get<ns::ecs::Physics>()->getVelocity()*10.f);

    // moving and rotating the shape around the sprite
    auto& shape = get<ns::ecs::ConvexShape>()->getDrawable();
    m_rotation += 5;
    shape.setRotation(m_rotation);
    shape.setPosition({ std::cos(ns::to_radian(m_rotation/2.f))*40, std::sin(ns::to_radian(m_rotation/2.f))*40 });

    // if Player is not moving (drection x == 0), set anim state to idle
    if (get<ns::ecs::Physics>()->getDirection().x == 0)
        get<ns::ecs::Sprite>()->setAnimState("idle");
}
