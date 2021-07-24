// Created by Modar Nasser on 17/07/2021.

#pragma once

#include <utility>
#include <functional>
#include <SFML/Graphics.hpp>
#include "NasNas/tween/Easing.hpp"

namespace ns::tween {
    using EasingFunction = std::function<float(float)>;
    using CallbackFunction = std::function<void(float)>;

    class Tween {
    public:
        std::vector<float> m_starts;
        std::vector<float> m_ends;
        std::vector<float> m_durations = {1.f};
        std::vector<float> m_delays = {0.f};
        std::vector<EasingFunction> m_easing_fns = {easing::linear};
        std::vector<CallbackFunction> m_on_step_cbs = {[](float){}};
        unsigned m_index = 0;
        float m_initial_delay = 0.f;
        float m_current_delay = 0.f;
        bool m_first_run = true;
        sf::Clock m_clock;
        bool m_loop = false;
        inline auto interpolate(unsigned i, float x) const -> float { return (m_ends[i] - m_starts[i]) * x + m_starts[i]; };
        void emplaceAnimation() {
            m_durations.emplace_back(1.f);
            m_easing_fns.empty() ?
                m_easing_fns.emplace_back(easing::linear) :
                m_easing_fns.emplace_back(m_easing_fns.back());
            m_on_step_cbs.empty() ?
                m_on_step_cbs.emplace_back() :
                m_on_step_cbs.emplace_back(m_on_step_cbs.back());
            m_delays.emplace_back(0.f);
        }
    public:
        explicit Tween() = default;

        void clear() {
            m_starts.clear();
            m_ends.clear();
            m_durations = {1.f};
            m_delays = {1.f};
            m_easing_fns = {easing::linear};
            m_on_step_cbs = {[](float){}};
            m_index = 0;
            m_initial_delay = 0.f;
            m_current_delay = 0.f;
            m_clock.restart();
            m_loop = false;
        }

        auto after(float delay) -> Tween& {
            m_initial_delay = delay;
            return *this;
        }

        auto from_to(float s, float e) -> Tween& {
            if (!m_starts.empty()) {
                m_index++;
                emplaceAnimation();
            }
            m_starts.emplace_back(s);
            m_ends.emplace_back(e);
            return *this;
        }

        auto to(float e) -> Tween& {
            if (!m_starts.empty()) {
                m_index++;
                m_starts.emplace_back(m_ends.back());
                emplaceAnimation();
                m_ends.emplace_back(e);
            }
            return *this;
        }

        auto during(float duration) -> Tween& {
            m_durations[m_index] = duration;
            return *this;
        };

        auto apply(CallbackFunction on_step_callback) -> Tween& {
            m_on_step_cbs[m_index] = std::move(on_step_callback);
            return *this;
        };

        auto with(const std::function<float(float)>& fn) -> Tween& {
            m_easing_fns[m_index] = fn;
            return *this;
        };

        auto delay(float delay) -> Tween& {
            m_delays[m_index] = delay;
            return *this;
        }

        void restart() {
            m_index = 0;
            m_current_delay = m_initial_delay;
            m_clock.restart();
            m_on_step_cbs[0](m_starts[0]);
        };

        auto loop() -> Tween& {
            m_loop = true;
            return *this;
        }

        auto ended() const -> bool {
            return m_index >= m_starts.size();
        };

        auto step() -> float {
            if (m_first_run) {
                restart();
                m_first_run = false;
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
                    restart();
                    return 0.f;
                } else
                    return 1.f;
            }

            auto pt = m_clock.getElapsedTime().asSeconds() / m_durations[m_index];

            auto& easing_fn = m_easing_fns[m_index];
            auto& callback = m_on_step_cbs[m_index];

            if (pt < 1.f)
                callback(interpolate(m_index, easing_fn(pt)));
            else {
                callback(m_ends[m_index]);
                m_clock.restart();
                m_current_delay = m_delays[m_index];
                m_index += 1;
            }
            return std::clamp(pt, 0.f, 1.f);
        }
    };

}
