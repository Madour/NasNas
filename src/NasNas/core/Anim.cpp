/**
* Created by Modar Nasser on 25/04/2020.
**/

#include "NasNas/core/Anim.hpp"

#include <utility>

using namespace ns;


AnimFrame::AnimFrame(const IntRect& rectangle, int duration, const sf::Vector2i& origin) :
rectangle(rectangle),
duration(duration),
origin(origin)
{}

Anim::Anim() = default;

Anim::Anim(std::vector<AnimFrame>  frames, bool loop):
m_frames(std::move(frames)),
loop(loop)
{}

void Anim::add(const AnimFrame& frame) {
    m_frames.push_back(frame);
}

auto Anim::getFrame(int index) -> const AnimFrame& {
    return m_frames[index];
}

auto Anim::frameCount() -> int {
    return m_frames.size();
}

