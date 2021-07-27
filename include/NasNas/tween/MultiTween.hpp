// Created by Modar Nasser on 27/07/2021.

#pragma once

#include <array>
#include "NasNas/tween/Tween.hpp"
#include "NasNas/tween/Easing.hpp"

namespace ns {
    template <unsigned N, typename = std::enable_if_t<N != 0 && N != 1>>
    class MultiTween {
    public:
        MultiTween();

        std::vector<std::array<float, N>> m_starts;
        std::vector<std::array<float, N>> m_ends;
        std::vector<std::array<float, N>> m_durations;
        std::vector<std::array<float, N>> m_delays;
        std::vector<tween::EasingFunction> m_easing_fns = {easing::linear};
        std::vector<tween::CallbackFunction> m_on_step_cbs = {[](float){}};
        unsigned m_index = 0;
        float m_initial_delay = 0.f;
        float m_current_delay = 0.f;
        bool m_first_run = true;
        bool m_loop = false;
    };

    template <unsigned N, typename E>
    MultiTween<N, E>::MultiTween() {
        m_durations.emplace_back();
        m_delays.emplace_back();
        m_durations.back().fill(1.f);
        m_delays.back().fill(0.f);
    }
}
