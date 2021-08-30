/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player() {
    add<ns::ecs::Transform>();

    // create Player spritesheet and set its animations
    m_spritesheet = std::make_unique<ns::Spritesheet>("adventurer", ns::Res::getTexture("adventurer.png"));
    m_spritesheet->setGrid({50, 37}, 7);
    m_spritesheet->addAnim("idle", 0, 4, 200, {25, 37});
    m_spritesheet->addAnim("walk", 8, 6, 100, {25, 37});
    // add sprite component to player (from spritesheet defined above)
    add<ns::ecs::Sprite>(m_spritesheet.get());

    // add physics component to player
    add<ns::ecs::Physics>(sf::Vector2f(0.5f, 5.f), 2.f, sf::Vector2f(0.2f, 0.f));

    // add inputs component to player and binding buttons to Player methods
    auto& inputs = add<ns::ecs::InputsComponent>();
    inputs.bind(ns::Inputs::getButton("left"), [&](){ moveLeft(); });
    inputs.bind(ns::Inputs::getButton("right"), [&](){ moveRight(); });
    inputs.onPress(ns::Inputs::getButton("up"), [&](){ jump(); });

    auto& collider = add<ns::ecs::AABBCollider>();
    collider.dynamic = true;
    collider.position = {0, -15};
    collider.size = {12, 28};

    auto rectangle_coll = sf::RectangleShape(collider.size);
    rectangle_coll.setOrigin(rectangle_coll.getSize()/2.f);
    rectangle_coll.setFillColor({255, 0, 0, 100});
    add<ns::ecs::RectangleShape>(rectangle_coll, collider.position);
}

void Player::jump() {
    get<ns::ecs::Physics>().setVelocityY(-5.f);
}

void Player::moveLeft() {
    get<ns::ecs::Physics>().applyForce({-0.4f, 0.f});
    get<ns::ecs::Sprite>().getDrawable().setScale(-1, 1);
}
void Player::moveRight() {
    get<ns::ecs::Physics>().applyForce({0.4f, 0.f});
    get<ns::ecs::Sprite>().getDrawable().setScale(1, 1);
}

auto Player::getPosition() const -> sf::Vector2f {
    return get<ns::ecs::Transform>().getPosition();
}

auto Player::getGlobalBounds() const -> ns::FloatRect {
    return get<ns::ecs::Transform>().getTransform().transformRect(
                get<ns::ecs::Sprite>().getGlobalBounds()
    );
}

void Player::update() {
    if (std::abs(get<ns::ecs::Physics>().getVelocity().x) <= 0.5f)
        get<ns::ecs::Sprite>().setAnimState("idle");
    else
        get<ns::ecs::Sprite>().setAnimState("walk");
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= get<ns::ecs::Transform>().getTransform();
    target.draw(get<ns::ecs::Sprite>(), states);
    if (ns::Settings::debug_mode)
        target.draw(get<ns::ecs::RectangleShape>(), states);
}