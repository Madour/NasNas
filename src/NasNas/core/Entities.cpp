/**
* Created by Modar Nasser on 15/04/2020.
**/

#include "NasNas/core/Entities.hpp"
#include <cmath>

using namespace ns;

BaseEntity::BaseEntity(const std::string &name, const std::string& default_anim_state) {
    m_name = name;
    m_anim_state = default_anim_state;
}

BaseEntity::BaseEntity(const std::string& name, Sprite* sprite_data, const std::string& default_anim_state)
: m_spr_data(sprite_data) {
    m_name = name;
    m_anim_state = default_anim_state;
    setSprite(sprite_data);
}

BaseEntity::~BaseEntity() = default;

void BaseEntity::setSprite(Sprite* sprite_data) {
    m_spr_data = sprite_data;

    m_anim_player.play(sprite_data->getAnim(m_anim_state));

    m_sprite = sf::Sprite(*sprite_data->texture);
    m_sprite.setTextureRect(m_anim_player.getActiveFrame().rectangle);
    m_sprite.setOrigin(m_anim_player.getActiveFrame().origin.x, m_anim_player.getActiveFrame().origin.y);
}

auto BaseEntity::getPosition() -> sf::Vector2f {
    return sf::Vector2f(getX(), getY());
}
void BaseEntity::setPosition(const sf::Vector2f& pos) {
    setX(pos.x);
    setY(pos.y);
}
void BaseEntity::setPosition(float x, float y) {
    setX(x);
    setY(y);
}

auto BaseEntity::getX() const -> float {
    return ((float)m_gx + m_rx) * 16;
}
void BaseEntity::setX(float value) {
    m_gx = (int)value / 16;
    m_rx = (value - (float)m_gx * 16) / 16;
}

auto BaseEntity::getY() const -> float {
    return ((float)m_gy + m_ry) * 16;
}
void BaseEntity::setY(float value) {
    m_gy = (int)value / 16;
    m_ry = (value - (float)m_gy * 16) / 16;
}

auto BaseEntity::getVelocity() const -> sf::Vector2f {
    return m_velocity;
}
void BaseEntity::setVelocity(float dx, float dy) {
    m_velocity.x = dx;
    m_velocity.y = dy;
}

void BaseEntity::update() {
    m_anim_player.update();
    if (m_sprite.getTextureRect() != m_anim_player.getActiveFrame().rectangle) {
        m_sprite.setTextureRect(m_anim_player.getActiveFrame().rectangle);
        m_sprite.setOrigin(m_anim_player.getActiveFrame().origin.x, m_anim_player.getActiveFrame().origin.y);
    }
}

void BaseEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}

void BaseEntity::move(float offsetx, float offsety) {
    if (std::abs(m_velocity.x) < std::abs(offsetx))
        m_velocity.x = m_acceleration.x * offsetx / std::abs(offsetx) + m_velocity.x;

    if (std::abs(m_velocity.y) < std::abs(offsety))
        m_velocity.y = m_acceleration.y * offsety / std::abs(offsety) + m_velocity.y;
}

