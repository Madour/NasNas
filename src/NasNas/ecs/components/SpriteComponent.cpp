/**
* Created by Modar Nasser on 10/06/2020.
**/


#include <NasNas/ecs/components/SpriteComponent.hpp>

#include <iostream>

using namespace ns;
using namespace ns::ecs;

SpriteComponent::SpriteComponent(SpriteSheet* spritesheet, const sf::Vector2f& pos_offset) :
SpriteComponent(spritesheet, "", pos_offset)
{}

SpriteComponent::SpriteComponent(SpriteSheet* spritesheet, const std::string& anim_state, const sf::Vector2f& pos_offset) {
    m_transform.translate(pos_offset);
    setSpritesheet(spritesheet);
    anim_state.empty() ? setAnimState(spritesheet->getAnimsMap().begin()->first) : setAnimState(anim_state);
}

void SpriteComponent::setSpritesheet(SpriteSheet* spritesheet) {
    m_spritesheet = spritesheet;
    if (spritesheet->getTexture() != nullptr)
        m_drawable.setTexture(*spritesheet->getTexture());
}

auto SpriteComponent::getAnimState() const -> const std::string& {
    return m_anim_player.getAnim()->getName();
}

void SpriteComponent::setAnimState(const std::string& anim_state) {
    if (m_spritesheet) {
        try {
            m_anim_player.play(m_spritesheet->getAnim(anim_state));
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
    return m_transform.transformRect(m_drawable.getGlobalBounds());
}

void SpriteComponent::update() {
    m_anim_player.update(m_drawable);
}

void SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= m_transform;
    target.draw(m_drawable, states);
}
