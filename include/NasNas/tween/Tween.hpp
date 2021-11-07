// Created by Modar Nasser on 17/07/2021.

#pragma once

#include <utility>
#include <SFML/Graphics.hpp>
#include "NasNas/tween/Easing.hpp"

namespace ns {

    class Tween {
    public:
        explicit Tween() = default;

        void clear();

        auto loop() -> Tween&;

        auto after(float delay) -> Tween&;

        auto from_to(float start, float end) -> Tween&;

        auto to(float end) -> Tween&;

        auto during(float duration) -> Tween&;

        auto apply(tween::CallbackFunction callback) -> Tween&;

        auto with(tween::EasingFunction function) -> Tween&;

        auto delay(float delay) -> Tween&;

        void onEnd(std::function<void()> fn);

        void restart();

        auto ended() const -> bool;

        auto step() -> float;

    private:
        sf::Clock m_clock;
        std::vector<float> m_starts;
        std::vector<float> m_ends;
        std::vector<float> m_durations = {1.f};
        std::vector<float> m_delays = {0.f};
        std::vector<tween::EasingFunction> m_easing_fns = {easing::linear};
        std::vector<tween::CallbackFunction> m_on_step_cbs = {[](float){}};
        std::function<void()> m_on_end_cb;
        unsigned m_index = 0;
        float m_initial_delay = 0.f;
        float m_current_delay = 0.f;
        bool m_first_run = true;
        bool m_on_end_called = false;
        bool m_loop = false;

        inline auto interpolate(unsigned i, float x) const -> float {
            return (m_ends[i] - m_starts[i]) * x + m_starts[i];
        };

        void emplaceAnimation();
    };

}
