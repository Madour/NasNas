/**
* Created by Modar Nasser on 25/04/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>

#include "NasNas/core/Anim.hpp"


namespace ns {

    class Sprite {
    public:
        Sprite(std::string name, const sf::Texture& texture, std::unordered_map<std::string, Anim> anims);
        ~Sprite();

        auto getAnim(const std::string& anim_name) -> const Anim&;

        const std::string name;
        const sf::Texture* texture;

    private:
        std::unordered_map<std::string, Anim> m_anims;
    };

}
