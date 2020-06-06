/**
* Created by Modar Nasser on 15/04/2020.
**/

#include "NasNas/core/Entities.hpp"
#include <cmath>

using namespace ns;

BaseEntity::BaseEntity() = default;

BaseEntity::BaseEntity(const std::string &name, const std::string& default_anim_state) {
    this->name = name;
    this->anim_state = default_anim_state;
}

BaseEntity::BaseEntity(const std::string& name, Sprite* sprite_data, const std::string& default_anim_state) :
data(sprite_data) {
    this->name = name;
    this->anim_state = default_anim_state;
    this->setSprite(sprite_data);
}

BaseEntity::~BaseEntity() = default;

void BaseEntity::setSprite(Sprite* sprite_data) {
    this->data = sprite_data;

    this->anim_player.play(sprite_data->getAnim(this->anim_state));

    this->sprite = sf::Sprite(*sprite_data->texture);
    this->sprite.setTextureRect(anim_player.getActiveFrame().rectangle);
    this->sprite.setOrigin(anim_player.getActiveFrame().origin.x, anim_player.getActiveFrame().origin.y);
}

auto BaseEntity::getPosition() -> sf::Vector2f {
    return sf::Vector2f(this->getX(), this->getY());
}
void BaseEntity::setPosition(const sf::Vector2f& pos) {
    this->setX(pos.x);
    this->setY(pos.y);
}
void BaseEntity::setPosition(float x, float y) {
    this->setX(x);
    this->setY(y);
}

auto BaseEntity::getX() const -> float {
    return ((float)this->gx + this->rx)*16;
}
void BaseEntity::setX(float value) {
    this->gx = (int)value/16;
    this->rx = (value - (float)this->gx * 16)/16;
}

auto BaseEntity::getY() const -> float {
    return ((float)this->gy + this->ry)*16;
}
void BaseEntity::setY(float value) {
    this->gy = (int)value/16;
    this->ry = (value - (float)this->gy * 16)/16;
}

auto BaseEntity::getVelocity() const -> sf::Vector2f {
    return this->velocity;
}
void BaseEntity::setVelocity(float dx, float dy) {
    this->velocity.x = dx;
    this->velocity.y = dy;
}

void BaseEntity::update() {
    this->setX(std::round(this->getX() + this->velocity.x));
    this->setY(std::round(this->getY() + this->velocity.y));
    this->sprite.setPosition(this->getX(), this->getY());

    this->velocity = sf::Vector2f(this->velocity.x* 0.98, this->velocity.y*0.98);
    this->anim_player.update();
    if (this->sprite.getTextureRect() != this->anim_player.getActiveFrame().rectangle) {
        this->sprite.setTextureRect(this->anim_player.getActiveFrame().rectangle);
        this->sprite.setOrigin(this->anim_player.getActiveFrame().origin.x, this->anim_player.getActiveFrame().origin.y);
    }
}

void BaseEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(this->sprite, states);
}

void BaseEntity::move(float offsetx, float offsety) {
    if (std::abs(this->velocity.x) < std::abs(offsetx))
        this->velocity.x = this->acceleration.x*offsetx/std::abs(offsetx) + this->velocity.x;

    if (std::abs(this->velocity.y) < std::abs(offsety))
        this->velocity.y = this->acceleration.y*offsety/std::abs(offsety) + this->velocity.y;
}

