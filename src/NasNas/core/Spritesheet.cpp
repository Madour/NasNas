/**
* Created by Modar Nasser on 25/04/2020.
**/

#include <utility>

#include "NasNas/core/Spritesheet.hpp"

using namespace ns;

// old constructor
/*
Spritesheet::Spritesheet(std::string name, const sf::Texture& texture, std::unordered_map<std::string, Anim*> anims):
name(std::move(name)),
texture(&texture),
m_anims_map(std::move(anims))
{}
*/

Spritesheet::Spritesheet(std::string  name, const sf::Texture& texture, const std::vector<Anim*>& anims):
name(std::move(name)),
texture(&texture)
{
    for(const auto& anim: anims) {
        m_anims_map[anim->getName()] = anim;
    }
}

Spritesheet::~Spritesheet() {
    for(auto& pair: m_anims_map) {
        delete(pair.second);
    }
}

auto Spritesheet::animsMap() -> const std::unordered_map<std::string, Anim*>& {
    return m_anims_map;
}

auto Spritesheet::getAnim(const std::string& anim_name) -> const Anim& {
    if(m_anims_map.count(anim_name) > 0)
        return *m_anims_map.at(anim_name);
    else
        throw std::invalid_argument("Accessing unexisting Anim "+anim_name+" in spritesheet "+name);
}

