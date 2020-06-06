/**
* Created by Modar Nasser on 25/04/2020.
**/

#include <utility>

#include "NasNas/core/Sprite.hpp"

using namespace ns;


AnimPlayer::AnimPlayer() = default;

void AnimPlayer::play(const Anim& animation) {
    m_anim = const_cast<Anim *>(&animation);
    m_index = 0;
    m_playing = true;
    m_clock = sf::Clock();
}

auto AnimPlayer::getActiveFrame() -> const AnimFrame& {
    if(m_anim != nullptr)
        return m_anim->frames[m_index];
    else {
        std::cout << "AnimPlayer doesn't have an Anim. Use AnimPlayer::play(Anim) first." << std::endl;
        std::exit(-1);
    }
}

void AnimPlayer::update() {
    if (m_playing) {
        if (m_clock.getElapsedTime().asMilliseconds() > m_anim->frames[m_index].duration) {
            m_index++;
            m_clock.restart();
            if (m_index >= m_anim->frames.size()) {
                if (m_anim->loop) {
                    m_index = 0;
                }
                else {
                    m_index--;
                    m_playing = false;
                }
            }
        }
    }
}


Sprite::Sprite(std::string name, const sf::Texture& texture, std::unordered_map<std::string, Anim> anims)
: name(std::move(name)),
texture(&texture),
m_anims(std::move(anims))
{}

auto Sprite::getAnim(const std::string&anim_name) -> const Anim& {
    return m_anims.at(anim_name);
}

Sprite::~Sprite() = default;
