// Created by Modar Nasser on 17/07/2021.

#include <SFML/Graphics.hpp>
#include <functional>
#include <utility>

#pragma once

namespace ns::tween {
    using EasingFunction = std::function<float(float)>;

    namespace easing {
        auto linear(float t) -> float {
            return t;
        };

        auto quadraticInOut(float t) -> float {
            if (t < 0.5f)
                return 2 * t * t;
            return 1 - (-2*t + 2) * (-2*t + 2) / 2.f;
        };

        auto sinusoidalIntOut(float t) -> float {
            return -std::cos(ns::PI * t) / 2.f + 0.5f;
        }

        auto bounceOut(float t) -> float {
            if (t < 1 / 2.75f) {
                return 7.5625f * t * t;
            } else if (t < 2.0f / 2.75f) {
                t -= 1.5f / 2.75f;
                return 7.5625f * t * t + .75f;
            } else if (t < 2.5f / 2.75f) {
                t -= 2.25f / 2.75f;
                return 7.5625f * t * t + .9375f;
            } else {
                t -= 2.625f / 2.75f;
                return 7.5625f * t * t + .984375f;
            }
        }

        auto elasticOut(float t) -> float {
            const float c4 = (2 * ns::PI) / 5;
            if (t == 0 || t == 1)
                return t;
            return std::pow(2.f, -10 * t) * std::sin((10 * t - 0.75f) * c4) + 1;
        }

        auto backIn(float t) -> float {
            const float c1 = 1.90158f;
            const float c3 = c1 + 1;
            return c3 * t * t * t - c1 * t * t;
        }

        auto backInOut(float t) -> float {
            const float c1 = 1.90158f;
            const float c2 = c1 * 1.525f;

            return t < 0.5
                   ? (pow(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2
                   : (pow(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;
        }
    }

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
        auto to(float t) -> Tween& { m_to =t; return *this; };
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
