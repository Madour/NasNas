/**
* Created by Modar Nasser on 10/06/2020.
**/


#include "NasNas/ecs/SpriteComponent.hpp"
#include "NasNas/ecs/BaseEntity.hpp"

using namespace ns;
using namespace ns::ecs;

SpriteComponent::SpriteComponent(BaseEntity* entity, Spritesheet* spritesheet, const sf::Vector2f& pos_offset) :
SpriteComponent(entity, spritesheet, "", pos_offset)
{}

SpriteComponent::SpriteComponent(BaseEntity* entity, Spritesheet* spritesheet, const std::string& anim_state, const sf::Vector2f& pos_offset) :
GraphicsComponent(entity) {
    m_transform.translate(pos_offset);
    setSpritesheet(spritesheet);
    anim_state.empty() ? setAnimState(spritesheet->getAnimsMap().begin()->first) : setAnimState(anim_state);
}

void SpriteComponent::setSpritesheet(Spritesheet* spritesheet) {
    m_spritesheet = spritesheet;
    m_drawable.setTexture(*spritesheet->texture);
}

auto SpriteComponent::getAnimState() const -> const std::string& {
    return m_anim_player.getAnim()->getName();
}

void SpriteComponent::setAnimState(const std::string& anim_state) {
    if (m_spritesheet) {
        try {
            m_anim_player.play(m_spritesheet->getAnim(anim_state));
            m_drawable.setTextureRect(m_anim_player.getActiveFrame().rectangle);
            m_drawable.setOrigin((float)m_anim_player.getActiveFrame().origin.x, (float)m_anim_player.getActiveFrame().origin.y);
        }
        catch (std::invalid_argument& exception) {
            std::cout << exception.what() << std::endl;
            exit(-1);
        }
    }
}

auto SpriteComponent::getAnimPlayer() -> AnimPlayer& {
    return m_anim_player;
}

auto SpriteComponent::getDrawable() -> sf::Sprite& {
    return m_drawable;
}

auto SpriteComponent::getGlobalBounds() -> ns::FloatRect {
    return ns::FloatRect(m_entity->transform()->getTransform().transformRect(
            m_transform.transformRect(m_drawable.getGlobalBounds())
    ));
}

void SpriteComponent::update() {
    m_anim_player.update(m_drawable);
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= m_transform;
    target.draw(m_drawable, states);
}
