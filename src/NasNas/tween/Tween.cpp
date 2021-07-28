// Created by Modar Nasser on 17/07/2021.

#include "NasNas/tween/Tween.hpp"

using namespace ns;

void Tween::clear() {
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

auto Tween::after(float delay) -> Tween& {
    m_initial_delay = delay;
    return *this;
}

auto Tween::from_to(float s, float e) -> Tween& {
    if (!m_starts.empty()) {
        m_index++;
        emplaceAnimation();
    }
    m_starts.emplace_back(s);
    m_ends.emplace_back(e);
    return *this;
}

auto Tween::to(float e) -> Tween& {
    if (!m_starts.empty()) {
        m_index++;
        m_starts.emplace_back(m_ends.back());
        emplaceAnimation();
        m_ends.emplace_back(e);
    }
    return *this;
}

auto Tween::during(float duration) -> Tween& {
    m_durations[m_index] = duration;
    return *this;
}

auto Tween::apply(tween::CallbackFunction cb) -> Tween& {
    m_on_step_cbs[m_index] = std::move(cb);
    return *this;
}

auto Tween::with(tween::EasingFunction fn) -> Tween& {
    m_easing_fns[m_index] = std::move(fn);
    return *this;
}

auto Tween::delay(float delay) -> Tween& {
    m_delays[m_index] = delay;
    return *this;
}

void Tween::restart() {
    m_index = 0;
    m_current_delay = m_initial_delay;
    m_clock.restart();
    if (!m_starts.empty() && !m_first_run)
        m_on_step_cbs[0](m_starts[0]);
}

auto Tween::loop() -> Tween& {
    m_loop = true;
    return *this;
}

auto Tween::ended() const -> bool {
    return m_index >= m_starts.size();
}

auto Tween::step() -> float {
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

void Tween::emplaceAnimation() {
    m_durations.emplace_back(1.f);
    m_delays.emplace_back(0.f);
    m_easing_fns.emplace_back(m_easing_fns.back());
    m_on_step_cbs.emplace_back(m_on_step_cbs.back());
}
