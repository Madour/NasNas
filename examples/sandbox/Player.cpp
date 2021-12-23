/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player() {
    add<ns::ecs::Transform>();

    // create Player spritesheet and set its animations
    m_spritesheet.setTexture(ns::Res::getTexture("adventurer.png"));
    m_spritesheet.setGrid({50, 37}, 7);
    m_spritesheet.addAnim("idle", 0, 4, 200, {25, 37});
    m_spritesheet.addAnim("walk", 8, 6, 100, {25, 37});
    // add sprite component to player (from spritesheet defined above)
    add<ns::ecs::Sprite>(&m_spritesheet);

    // add physics component to player
    add<ns::ecs::Physics>(2.f, sf::Vector2f(0.2f, 0.2f), 1.f);

    // add shape component to player (blue square)
    auto convexshape = sf::ConvexShape(4);
    convexshape.setFillColor(sf::Color::Blue);
    convexshape.setPoint(0, {-5, -5});
    convexshape.setPoint(1, {5, -5});
    convexshape.setPoint(2, {5, 5});
    convexshape.setPoint(3, {-5, 5});
    add<ns::ecs::ConvexShape>(convexshape, sf::Vector2f(0, -15));

    auto velocity_vector = ns::LineShape();
    velocity_vector.resize(2);
    velocity_vector.setColor(0, sf::Color::Yellow);
    velocity_vector.setColor(1, sf::Color::Red);
    add<ns::ecs::LineShape>(velocity_vector);

    // add inputs component to player and binding buttons to Player methods
    auto& inputs = add<ns::ecs::InputsComponent>();
    inputs.bind(ns::Inputs::getButton("left"), [&](){ turnLeft(); });
    inputs.bind(ns::Inputs::getButton("right"), [&](){ turnRight(); });
    inputs.bind(ns::Inputs::getButton("up"), [&](){ moveForward(); });
    inputs.bind(ns::Inputs::getButton("down"), [&](){ moveBackward(); });

    auto& collider = add<ns::ecs::AABBCollider>();
    collider.dynamic = true;
    collider.position = {0, -15};
    collider.size = {16, 28};

    auto rectangle_coll = sf::RectangleShape(collider.size);
    rectangle_coll.setOrigin(rectangle_coll.getSize()/2.f);
    rectangle_coll.setFillColor({255, 0, 0, 100});
    add<ns::ecs::RectangleShape>(rectangle_coll, collider.position);
}

void Player::moveForward() {
    get<ns::ecs::Physics>().applyForce(get<ns::ecs::Physics>().getDirection());
}

void Player::moveBackward() {
    get<ns::ecs::Physics>().applyForce(-get<ns::ecs::Physics>().getDirection());
}

void Player::turnLeft() {
    get<ns::ecs::Physics>().applyTorque(-0.05f);
}

void Player::turnRight() {
    get<ns::ecs::Physics>().applyTorque(0.05f);
}

void Player::moveLeft() {
    get<ns::ecs::Physics>().applyForce({-0.4f, 0.f});
    get<ns::ecs::Sprite>().getDrawable().setScale(-1, 1);
}
void Player::moveRight() {
    get<ns::ecs::Physics>().applyForce({0.4f, 0.f});
    get<ns::ecs::Sprite>().getDrawable().setScale(1, 1);
}
void Player::moveUp() {
    get<ns::ecs::Physics>().applyForce({0.0f, -0.4f});
}
void Player::moveDown() {
    get<ns::ecs::Physics>().applyForce({0.0f, 0.4f});
}

auto Player::getPosition() const -> sf::Vector2f {
    return get<ns::ecs::Transform>().getPosition();
}

auto Player::getGlobalBounds() const -> ns::FloatRect {
    return get<ns::ecs::Transform>().getTransform().transformRect(
            ns::utils::computeBounds({
                get<ns::ecs::Sprite>().getGlobalBounds(),
                get<ns::ecs::ConvexShape>().getGlobalBounds(),
                get<ns::ecs::LineShape>().getGlobalBounds()
            })
    );
}

void Player::update() {
    // update velocity vector
    auto& vel_vec = get<ns::ecs::LineShape>().getDrawable();
    vel_vec.setPoint(1, get<ns::ecs::Physics>().linear_velocity * 10.f);

    get<ns::ecs::Sprite>().getDrawable().setRotation(get<ns::ecs::Physics>().getAngle());

    // move and rotate the shape around the sprite
    auto& shape = get<ns::ecs::ConvexShape>().getDrawable();
    m_rotation += 5;
    shape.setRotation(m_rotation);
    shape.setPosition({ std::cos(ns::to_radian(m_rotation/2.f))*40, std::sin(ns::to_radian(m_rotation/2.f))*40 });

    // if Player is not moving set anim state to idle
    auto& velocity = get<ns::ecs::Physics>().linear_velocity;
    if (std::abs(velocity.x) <= 0.1f && std::abs(velocity.y) <= 0.1f)
        get<ns::ecs::Sprite>().setAnimState("idle");
    else
        get<ns::ecs::Sprite>().setAnimState("walk");
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= get<ns::ecs::Transform>().getTransform();
    target.draw(get<ns::ecs::Sprite>(), states);
    target.draw(get<ns::ecs::ConvexShape>(), states);
    if (ns::Settings::debug_mode)
        target.draw(get<ns::ecs::RectangleShape>(), states);
    target.draw(get<ns::ecs::LineShape>(), states);
}