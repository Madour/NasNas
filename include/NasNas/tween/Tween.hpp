// Created by Modar Nasser on 17/07/2021.

#include <utility>
#include <functional>

#include <SFML/Graphics.hpp>

#include "NasNas/tween/Easing.hpp"

#pragma once

#include <iostream>

namespace ns::tween {
    using EasingFunction = std::function<float(float)>;

    class Tween {
    public:
        std::vector<float> m_starts;
        std::vector<float> m_ends;
        std::vector<float> m_durations;
        std::vector<float> m_delays;
        std::vector<EasingFunction> m_easing_fns;
        std::vector<std::function<void(float)>> m_on_step_cbs;
        unsigned m_index = 0;
        float m_current_delay = 0.f;
        float m_time = 0.f;
        sf::Clock m_clock;
        bool m_loop = false;
        inline auto interpolate(unsigned i, float x) const -> float { return (m_ends[i] - m_starts[i]) * x + m_starts[i]; };

    public:
        explicit Tween() = default;


        auto from(float f) -> Tween& {
            m_starts.emplace_back(f);
            return *this;
        }

        auto to(float t) -> Tween& {
            if (m_ends.size() + 1 > m_starts.size()) {
                m_starts.emplace_back(m_ends.back());
            }
            if (m_ends.size() + 1 > m_delays.size()) {
                m_delays.emplace_back(0.f);
            }
            m_ends.emplace_back(t);
            return *this;
        };

        auto during(float duration) -> Tween& {
            m_durations.emplace_back(duration);
            return *this;
        };

        auto apply(std::function<void(float)> on_step_callback) -> Tween& {
            m_on_step_cbs.emplace_back(std::move(on_step_callback));
            return *this;
        };

        auto with(const std::function<float(float)>& fn) -> Tween& {
            m_easing_fns.emplace_back(fn);
            return *this;
        };

        auto delay(float delay) -> Tween& {
            m_delays.emplace_back(delay);
            return *this;
        }

        void restart() {
            m_time = 0;
            m_clock.restart();
        };

        auto loop() -> Tween& {
            m_loop = true;
            return *this;
        }

        auto ended() const -> bool {
            return m_index >= m_starts.size();
        };

        auto step() -> float {
            static bool first = true;
            if (first) {
                m_current_delay = m_delays[0];
                m_clock.restart();
                first = false;
            }

            if (m_current_delay > 0.f) {
                if (m_clock.getElapsedTime().asSeconds() < m_current_delay)
                    return 0.f;
                else {
                    m_current_delay = 0.f;
                    m_clock.restart();
                }
            }

            if (ended()) {
                if (m_loop) {
                    m_index = 0;
                    m_current_delay = m_delays[0];
                    m_clock.restart();
                    m_on_step_cbs[0](m_starts[0]);
                    return 0.f;
                }
                else
                    return 1.f;
            }

            m_time = m_clock.getElapsedTime().asSeconds();
            auto pt = m_time / m_durations[m_index];

            auto& easing_fn = m_index >= m_easing_fns.size() ? m_easing_fns.back() : m_easing_fns[m_index];
            auto& callback = m_index >= m_on_step_cbs.size() ? m_on_step_cbs.back() : m_on_step_cbs[m_index];

            if (pt < 1.f)
                callback(interpolate(m_index, easing_fn(pt)));
            else {
                callback(m_ends[m_index]);
                m_time = 0;
                m_clock.restart();
                m_index += 1;
                m_current_delay = m_delays[m_index];
                std::cout << m_index << " " << m_current_delay << std::endl;

            }
            return std::clamp(pt, 0.f, 1.f);
        }
    };
}
