// Created by Modar Nasser on 18/07/2021.

#pragma once

namespace ns::easing {
    auto linear(float t) -> float;

    auto quadraticInOut(float t) -> float;

    auto sinusoidalIntOut(float t) -> float;

    auto bounceOut(float t) -> float;

    auto elasticOut(float t) -> float;

    auto backIn(float t) -> float;
    auto backInOut(float t) -> float;

    namespace custom {
        template <unsigned C1>
        auto backIn(float t) -> float;

        template <unsigned C1>
        auto backIn2(float t) -> float;

        template <unsigned C1>
        auto backInOut2(float t) -> float;

        template <unsigned C1>
        auto backIn(float t) -> float {
            const float c1 = C1/10.f;
            const float c3 = c1 + 1.f;
            return c3 * t * t * t - c1 * t * t;
        }
        template <unsigned C>
        auto backIn2(float t) -> float {
            return C * t*t - (C - 1.f) * t;
        }
        template <unsigned C>
        auto backInOut2(float t) -> float {
            const int c = C;
            if (t < 0.5f) {
                return c * (1.4142f*t)*(1.4142f*t) - (c - 1.f) * t;
            }
            t -= 1;
            return -c * (1.4142f*t)*(1.4142f*t) - (c - 1.f) * t + 1;
        }
    }

}
