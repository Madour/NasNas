/**
* Created by Modar Nasser on 08/06/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include "NasNas/core/Anim.hpp"

namespace ns::ecs {

    class AnimPlayer {
    public:
        explicit AnimPlayer();
        auto getActiveFrame() -> const AnimFrame &;
        void play(const Anim &animation);
        void setPlaySpeed(float speed);
        void update();

    private:
        Anim *m_anim = nullptr;
        int m_index = 0;
        bool m_playing = false;
        float m_play_speed = 1;
        sf::Clock m_clock;
    };
}
