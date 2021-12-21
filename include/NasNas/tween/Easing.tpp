// Created by Modar Nasser on 24/07/2021.

#pragma once

#include <NasNas/core/data/Maths.hpp>

namespace ns {
    //// Polynomial easing functions //////////////////////////////////
    template <unsigned Degree>
    auto easing::custom::polynomialIn(float t) -> float {
        return static_cast<float>(std::pow(t, Degree));
    }
    template <unsigned Degree>
    auto easing::custom::polynomialOut(float t) -> float {
        return 1 - easing::custom::polynomialIn<Degree>(1 - t);
    }
    template <unsigned Degree>
    auto easing::custom::polynomialInOut(float t) -> float {
        if (t < 0.5f)
            return static_cast<float>(std::pow(2.f, Degree-1) * polynomialIn<Degree>(t));
        return static_cast<float>(1 - std::pow(-2.f * t + 2.f, Degree) / 2.f);
    }

    //// Back easing functions //////////////////////////////////
    template <unsigned Pull>
    auto easing::custom::backIn(float t) -> float {
        const float pull = Pull/10.f;
        return (pull + 1.f) * t * t * t - pull * t * t;
    }
    template <unsigned Pull>
    auto easing::custom::backOut(float t) -> float {
        return 1 - easing::custom::backIn<Pull>(1 - t);
    }
    template <unsigned Pull>
    auto easing::custom::backInOut(float t) -> float {
        const float pull = 1.525f * Pull/10.f;
        if (t < 0.5f)
            return 2*t*t * (2*t * (pull+1) - pull);
        return 2*(t-1)*(t-1) * (2 * (pull+1) * (t-1) + pull) + 1;
    }

    template <unsigned Pull>
    auto easing::custom::backIn2(float t) -> float {
        const float pull = Pull/10.f;
        return pull * t*t - (pull - 1.f) * t;
    }
    template <unsigned Pull>
    auto easing::custom::backOut2(float t) -> float {
        return 1 - easing::custom::backIn2<Pull>(1 - t);
    }
    template <unsigned Pull>
    auto easing::custom::backInOut2(float t) -> float {
        const float pull = Pull/10.f;
        if (t < 0.5f) {
            return pull * (1.4142f*t)*(1.4142f*t) - (pull - 1.f) * t;
        }
        t -= 1;
        return -pull * (1.4142f*t)*(1.4142f*t) - (pull - 1.f) * t + 1;
    }

    //// Elastic easing functions //////////////////////////////////
    template <unsigned Ondulation>
    auto easing::custom::elasticIn(float t) -> float {
        return 1 - elasticOut<Ondulation>(1 - t);
    }
    template <unsigned Ondulation>
    auto easing::custom::elasticOut(float t) -> float {
        if (t == 0 || t == 1)
            return t;
        const float ondul = Ondulation / 10.f;
        return std::pow(2.f, -10 * t) * std::sin(2 * ns::PI * (ondul * t - 1.25f)) + 1;
    }
    template <unsigned Ondulation>
    auto easing::custom::elasticInOut(float t) -> float {
        if (t == 0 || t == 1)
            return t;
        const float atten = Ondulation == 0 ? 0.f : 1 / (Ondulation / 12.f);
        if (t < 0.5f)
            return  -std::pow(2.f, 20*t - 10) * std::sin(ns::PI * (20*t - 11.125f) * atten) / 2;
        else
            return std::pow(2.f, -20*t + 10) * std::sin(ns::PI * (20*t - 11.125f) * atten) / 2 + 1;
    }
}
