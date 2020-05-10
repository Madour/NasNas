/**
* Created by Modar Nasser on 25/04/2020.
**/

#include <utility>

#include "NasNas/core/Sprite.hpp"

using namespace ns;


AnimPlayer::AnimPlayer() = default;

void AnimPlayer::play(const Anim& animation) {
    this->anim = const_cast<Anim *>(&animation);
    this->index = 0;
    this->playing = true;
    this->clock = sf::Clock();
}

auto AnimPlayer::getActiveFrame() -> const AnimFrame& {
    return this->anim->frames[this->index];
}

void AnimPlayer::update() {
    if (this->playing) {
        if (this->clock.getElapsedTime().asMilliseconds() > this->anim->frames[this->index].duration) {
            this->index++;
            this->clock.restart();
            if (this->index >= this->anim->frames_count()) {
                if (this->anim->loop) {
                    this->index = 0;
                }
                else {
                    this->index--;
                    this->playing = false;
                }

            }
        }
    }
}

//////////////////////////////////

Sprite::Sprite(std::string name, const sf::Texture& texture, std::unordered_map<std::string, Anim> anims):
        name(std::move(name)),
        texture(&texture),
        anims(std::move(anims))
{}

auto Sprite::getAnim(const std::string&anim_name) -> const Anim& {
    return this->anims.at(anim_name);
}

Sprite::~Sprite() = default;
