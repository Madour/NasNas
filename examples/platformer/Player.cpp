/**
* Created by Modar Nasser on 07/06/2020.
**/

#include "Player.hpp"

Player::Player() {
    add<ns::ecs::Transform>();

    // create Player spritesheet and set its animations
    m_spritesheet = std::make_unique<ns::Spritesheet>("adventurer", ns::Res::getTexture("adventurer.png"));
    m_spritesheet->setGrid({50, 37}, 7);
    m_spritesheet->addAnim("idle", 0, 4, 100, {25, 37});
    m_spritesheet->addAnim("walk", 8, 6, 100, {25, 37});
    m_spritesheet->addAnim("jump", 16, 2, {100, 150}, {25, 34});
    m_spritesheet->getAnim("jump").loop = false;
    m_spritesheet->addAnim("air_roll", 18, 4, 100, {25, 30});
    m_spritesheet->addAnim("fall", 22, 2, 80, {25, 34});
    m_spritesheet->addAnim("land", 14, 2, 90, {25, 37});
    m_spritesheet->getAnim("land").loop = false;
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
    if (!m_double_jump)
        get<ns::ecs::Physics>().setVelocityY(-4.f);
    auto& state = get<ns::ecs::Sprite>().getAnimState();
    m_double_jump = m_in_air ? true : false;
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
    static bool inputs_enabled = true;
    auto& velocity = get<ns::ecs::Physics>().getVelocity();
    auto& sprite = get<ns::ecs::Sprite>();
    auto& inputs = get<ns::ecs::Inputs>();
    if (std::abs(velocity.y) <= 0.1f && sprite.getAnimState() != "jump" && sprite.getAnimState() != "air_roll") {
        m_in_air = false;
        if (sprite.getAnimState() == "fall" && (m_double_jump || m_must_land)) {
            sprite.setAnimState("land");
            inputs.disable();
            inputs_enabled = false;
        }
        else if (!sprite.getAnimPlayer().isPlaying()) {
            inputs.enable();
            inputs_enabled = true;
        }
        if (inputs_enabled) {
            m_double_jump = false;
            if (std::abs(velocity.x) <= 0.5f)
                sprite.setAnimState("idle");
            else
                sprite.setAnimState("walk");
        }
    }
    else if (velocity.y < 0) {
        m_in_air = true;
        if (m_double_jump)
            sprite.setAnimState("air_roll");
        else
            sprite.setAnimState("jump");
    }
    else if (velocity.y >= 0) {
        m_in_air = true;
        sprite.setAnimState("fall");
        m_must_land = velocity.y > 4.5f;
    }
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= get<ns::ecs::Transform>().getTransform();
    target.draw(get<ns::ecs::Sprite>(), states);
    if (ns::Settings::debug_mode)
        target.draw(get<ns::ecs::RectangleShape>(), states);
}