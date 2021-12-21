// Created by Modar Nasser on 27/07/2021.

#pragma once

#include <array>
#include <functional>
#include <type_traits>
#include <vector>

#include <NasNas/tween/Easing.hpp>

namespace ns {
    template <unsigned N, typename = std::enable_if_t<N != 0 && N != 1>>
    class MultiTween {
    public:
        MultiTween();

        void clear();

        auto loop() -> MultiTween<N>&;

        auto after(float delay) -> MultiTween<N>&;

        auto from_to(const std::array<float, N>& start, const std::array<float, N>& end) -> MultiTween<N>&;

        auto to(const std::array<float, N>& end) -> MultiTween<N>&;

        auto during(float duration) -> MultiTween<N>&;

        auto apply(tween::MultiCallbackFunction<N> cb) -> MultiTween<N>&;

        auto with(const tween::EasingFunction& fn) -> MultiTween<N>&;
        auto with(std::array<tween::EasingFunction, N> fn) -> MultiTween<N>&;

        auto delay(float delay) -> MultiTween<N>&;

        void onEnd(std::function<void()> fn);

        void restart();

        auto ended() const -> bool;

        auto step() -> float;

    private:
        sf::Clock m_clock;
        std::vector<std::array<float, N>> m_starts;
        std::vector<std::array<float, N>> m_ends;
        std::vector<float> m_durations;
        std::vector<float> m_delays;
        std::vector<std::array<tween::EasingFunction, N>> m_easing_fns;
        std::vector<tween::MultiCallbackFunction<N>> m_on_step_cbs;
        std::function<void()> m_on_end_cb = []{};
        unsigned m_index = 0;
        float m_initial_delay = 0.f;
        float m_current_delay = 0.f;
        bool m_first_run = true;
        bool m_on_end_called = false;
        bool m_loop = false;

        inline void interpolate(unsigned index, std::array<float, N>& x) const {
            for (unsigned i = 0; i < N; ++i) {
                x[i] = (m_ends[index][i] - m_starts[index][i]) * x[i] + m_starts[index][i];
            }
        }
        void emplaceAnimation();
    };

}

#include "MultiTween.tpp"
