// Created by Modar Nasser on 18/07/2021.

#include "NasNas/core/data/Maths.hpp"

#include "NasNas/tween/Easing.hpp"


auto ns::easing::linear(float t) -> float {
    return t;
};

auto ns::easing::quadraticInOut(float t) -> float {
    if (t < 0.5f)
        return 2 * t * t;
    return 1 - (-2*t + 2) * (-2*t + 2) / 2.f;
};

auto ns::easing::sinusoidalIntOut(float t) -> float {
    return -std::cos(ns::PI * t) / 2.f + 0.5f;
}

auto ns::easing::bounceOut(float t) -> float {
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

auto ns::easing::elasticOut(float t) -> float {
    const float c4 = (2 * ns::PI) / 4;
    if (t == 0 || t == 1)
        return t;
    return std::pow(2.f, -10 * t) * std::sin((10 * t - 0.75f) * c4) + 1;
}

auto ns::easing::backIn(float t) -> float {
    return custom::backIn<20>(t);
}

auto ns::easing::backInOut(float t) -> float {

    const float c1 = 2.f;
    const float c2 = c1 * 1.525f;

    if (t < 0.5f)
        return 2 * t * t * ((2 * t * c2 + 2 * t) - c2);
    return 2 * (t*t - 2*t + 1) * ((c2 + 1) * (t * 2 - 2) + c2) + 1;
}
