// Created by Modar Nasser on 17/07/2021.

#include <utility>
#include <functional>

#include <SFML/Graphics.hpp>

#include "NasNas/tween/Easing.hpp"

#pragma once

namespace ns::tween {
    using EasingFunction = std::function<float(float)>;

    class Tween {
        std::function<void(float)> m_onstep;
        EasingFunction m_function;
        float m_duration = 1.f;
        float m_from = 0.f;
        float m_to = 0.f;
        float m_time = 0.f;
        bool m_first_end = true;
        sf::Clock m_clock;
        inline auto interpolate(float x) const -> float { return (m_to - m_from) * x + m_from; };

    public:
        explicit Tween() = default;
        auto apply(std::function<void(float)> onStep) -> Tween& { m_onstep = std::move(onStep); return *this; };
        auto from(float f) -> Tween& { m_from = f; return *this; };
        auto to(float t) -> Tween& { m_to = t; return *this; };
        auto during(float duration) -> Tween& { m_duration = duration; return *this; };
        auto with(std::function<float(float)> fn) -> Tween& { m_function = std::move(fn); return *this; };
        void restart() { m_time = 0; m_first_end = true; m_clock.restart();}
        auto hasEnded() const -> bool { return m_time > m_duration; };
        auto step() -> float{
            static bool first = true;
            if (first) {
                m_clock.restart();
                first = false;
            }
            m_time = m_clock.getElapsedTime().asSeconds();
            auto pt = m_time / m_duration;
            if (pt < 1.f)
                m_onstep(interpolate(m_function(pt)));
            else {
                if (m_first_end)
                    m_onstep(m_to);
                m_first_end = false;
            }
            return std::min(pt, 1.f);
        }
    };
}
