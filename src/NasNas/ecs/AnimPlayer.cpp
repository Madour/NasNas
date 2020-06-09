/**
* Created by Modar Nasser on 08/06/2020.
**/

#include "NasNas/ecs/AnimPlayer.hpp"

using namespace ns::ecs;
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
        return m_anim->getFrame(m_index);
    else {
        std::cout << "AnimPlayer doesn't have an Anim. Use AnimPlayer::play(Anim) first." << std::endl;
        std::exit(-1);
    }
}

void AnimPlayer::setPlaySpeed(float speed) {
    if (speed > 0) {
        m_play_speed = speed;
    }
    else if (speed == 0) {
        m_playing = false;
    } else {
        std::cout << "Warning : AnimPlayer speed must be a positive value. Using absolute value." << std::endl;
        m_play_speed = std::abs(speed);
    }

}

void AnimPlayer::update() {
    if (m_playing) {
        if (m_clock.getElapsedTime().asMilliseconds() > (float)m_anim->getFrame(m_index).duration / m_play_speed) {
            m_index++;
            m_clock.restart();
            if (m_index >= m_anim->frameCount()) {
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
