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

////////////////////////

Anim::Anim(std::vector<AnimFrame>  frames, bool loop):
frames(std::move(frames)),
loop(loop)
{}

Anim::Anim() = default;

void Anim::add(const AnimFrame& frame) {
    this->frames.push_back(frame);
}

auto Anim::frames_count() const -> int {
    return this->frames.size();
}
