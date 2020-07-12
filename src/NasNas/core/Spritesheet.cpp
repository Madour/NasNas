/**
* Created by Modar Nasser on 25/04/2020.
**/


#include "NasNas/core/Spritesheet.hpp"

using namespace ns;

Spritesheet::Spritesheet(std::string  name, const sf::Texture& texture, const std::vector<Anim*>& anims) :
name(std::move(name)),
texture(&texture)
{
    for(const auto& anim: anims) {
        m_anims_map[anim->getName()] = anim;
    }
}

Spritesheet::~Spritesheet() {
    for(auto& [anim_name, anim]: m_anims_map) {
        delete(anim);
    }
}

auto Spritesheet::getAnimsMap() -> const std::unordered_map<std::string, Anim*>& {
    return m_anims_map;
}

auto Spritesheet::getAnim(const std::string& anim_name) -> const Anim& {
    if(m_anims_map.count(anim_name) > 0)
        return *m_anims_map.at(anim_name);
    else
        throw std::invalid_argument("Accessing unexisting Anim "+anim_name+" in spritesheet "+name);
}
