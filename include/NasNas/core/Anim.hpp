/**
* Created by Modar Nasser on 25/04/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include "NasNas/data/Rect.hpp"
#include <vector>

namespace ns {

    class AnimFrame {
    public:
        AnimFrame(const IntRect& rectangle, int duration, const sf::Vector2i& origin={0, 0});
        const IntRect rectangle;
        const int duration;
        const sf::Vector2i origin;
    };

    class Anim {
    public:
        Anim();
        explicit Anim(std::vector<AnimFrame> frames, bool loop=true);
        void add(const AnimFrame& frame);

        std::vector<AnimFrame> frames;
        auto frames_count() const -> int;
        bool loop = true;
    };

}
