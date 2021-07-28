// Created by Modar Nasser on 28/07/2021.

#pragma once

namespace ns {
    template <unsigned int N, typename E>
    MultiTween<N, E>::MultiTween() {
        clear();
    }

    template <unsigned int N, typename E>
    void MultiTween<N, E>::clear() {
        m_starts.clear();
        m_ends.clear();
        m_durations = {1.f};
        m_delays = {1.f};
        m_easing_fns.clear();
        m_easing_fns.emplace_back();
        m_easing_fns.back().fill(easing::linear);
        m_on_step_cbs = {[](std::array<float, N>){}};
        m_index = 0;
        m_initial_delay = 0.f;
        m_current_delay = 0.f;
        m_clock.restart();
        m_loop = false;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::loop() -> MultiTween<N>& {
        m_loop = true;
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::after(float delay) -> MultiTween<N>& {
        m_initial_delay = delay;
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::from_to(const std::array<float, N>& s, const std::array<float, N>& e) -> MultiTween<N>& {
        if (!m_starts.empty()) {
            m_index++;
            emplaceAnimation();
        }
        m_starts.emplace_back(s);
        m_ends.emplace_back(e);
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::to(const std::array<float, N>& e) -> MultiTween<N>& {
        if (!m_starts.empty()) {
            m_index++;
            m_starts.emplace_back(m_ends.back());
            emplaceAnimation();
            m_ends.emplace_back(e);
        }
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::during(float duration) -> MultiTween<N>& {
        m_durations[m_index] = duration;
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::apply(tween::MultiCallbackFunction<N> cb) -> MultiTween<N>& {
        m_on_step_cbs[m_index] = std::move(cb);
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::with(const tween::EasingFunction& fn) -> MultiTween<N>& {
        for (auto& easing : m_easing_fns[m_index]) {
            easing = fn;
        }
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::with(std::array<tween::EasingFunction, N> fn) -> MultiTween<N>& {
        m_easing_fns[m_index] = std::move(fn);
        return *this;
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::delay(float delay) -> MultiTween<N>& {
        m_delays[m_index] = delay;
        return *this;
    }

    template <unsigned int N, typename E>
    void MultiTween<N, E>::restart() {
        m_index = 0;
        m_current_delay = m_initial_delay;
        m_clock.restart();
        if (!m_starts.empty() && !m_first_run)
            m_on_step_cbs[0](m_starts[0]);
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::ended() const -> bool {
        return m_index >= m_starts.size();
    }

    template <unsigned int N, typename E>
    auto MultiTween<N, E>::step() -> float {
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

        auto& easing_fns = m_easing_fns[m_index];
        auto& callback = m_on_step_cbs[m_index];

        if (pt < 1.f) {
            std::array<float, N> values;
            for (unsigned i = 0; i < N; ++i) {
                values[i] = easing_fns[i](pt);
            }
            interpolate(m_index, values);
            callback(values);
        }
        else {
            callback(m_ends[m_index]);
            m_clock.restart();
            m_current_delay = m_delays[m_index];
            m_index += 1;
        }
        return std::clamp(pt, 0.f, 1.f);
    }

    template <unsigned int N, typename E>
    void MultiTween<N, E>::emplaceAnimation() {
        m_durations.emplace_back(1.f);
        m_delays.emplace_back(0.f);
        m_easing_fns.emplace_back(m_easing_fns.back());
        m_on_step_cbs.emplace_back(m_on_step_cbs.back());
    }

}
