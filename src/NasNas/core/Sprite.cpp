/**
* Created by Modar Nasser on 25/04/2020.
**/

#include <utility>

#include "NasNas/core/Sprite.hpp"

using namespace ns;


Sprite::Sprite(std::string name, const sf::Texture& texture, std::unordered_map<std::string, Anim> anims)
: name(std::move(name)),
texture(&texture),
m_anims(std::move(anims))
{}

auto Sprite::getAnim(const std::string&anim_name) -> const Anim& {
    return m_anims.at(anim_name);
}

Sprite::~Sprite() = default;
