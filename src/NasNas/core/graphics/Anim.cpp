/**
* Created by Modar Nasser on 25/04/2020.
**/

#include <NasNas/core/graphics/Anim.hpp>

#include <cmath>
#include <iostream>

using namespace ns;

AnimFrame::AnimFrame(const ns::IntRect& rectangle, int duration, const sf::Vector2i& origin) :
rectangle(rectangle),
duration(duration),
origin(origin)
{}


Anim::Anim() = default;

Anim::Anim(std::string name, std::vector<AnimFrame>  frames, bool loop) :
loop(loop),
m_name(std::move(name)),
m_frames(std::move(frames))
{}

void Anim::add(const AnimFrame& frame) {
    m_frames.push_back(frame);
}

auto Anim::getName() const -> const std::string& {
    return m_name;
}

auto Anim::getFrame(int index) const -> const AnimFrame& {
    return m_frames[index];
}

auto Anim::size() const -> int {
    return m_frames.size();
}


AnimPlayer::AnimPlayer() = default;

void AnimPlayer::play(const Anim& animation) {
    if (!m_anim || m_anim->getName() != animation.getName()) {
        m_anim = &animation;
        m_index = 0;
        m_playing = true;
        m_clock.restart();
    }
}

void AnimPlayer::replay(const Anim& animation) {
    m_anim = &animation;
    m_index = 0;
    m_playing = true;
    m_clock.restart();
}

void AnimPlayer::replay() {
    m_index = 0;
    m_playing = true;
    m_clock.restart();
}

void AnimPlayer::resume() {
    m_playing = true;
    m_clock.restart();
}

void AnimPlayer::pause() {
    m_playing = false;
}

void AnimPlayer::stop() {
    m_index = 0;
    m_playing = false;
}

auto AnimPlayer::isPlaying() const -> bool {
    return m_playing;
}

auto AnimPlayer::getAnim() const -> const Anim* {
    return m_anim;
}

auto AnimPlayer::getActiveFrame() const -> const AnimFrame& {
    if(m_anim != nullptr)
        return m_anim->getFrame(m_index);
    else {
        std::cerr << "AnimPlayer doesn't have an Anim. Use AnimPlayer::play(Anim) first." << std::endl;
        exit(-1);
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
            if (m_index >= m_anim->size()) {
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

void AnimPlayer::update(sf::Sprite& spr) {
    update();
    const auto& active_frame = getActiveFrame();
    spr.setTextureRect(active_frame.rectangle);
    spr.setOrigin(float(active_frame.origin.x), float(active_frame.origin.y));
}
