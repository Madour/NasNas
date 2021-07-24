// Created by Modar Nasser on 18/07/2021.

#pragma once

namespace ns {

    struct easing {
        static auto linear(float t) -> float;

        static auto quadraticInOut(float t) -> float;

        static auto sinusoidalIntOut(float t) -> float;

        static auto bounceIn(float t) -> float;
        static auto bounceOut(float t) -> float;

        static auto elasticIn(float t) -> float;
        static auto elasticOut(float t) -> float;
        static auto elasticInOut(float t) -> float;

        static auto backIn(float t) -> float;
        static auto backInOut(float t) -> float;

        struct custom {
            template <unsigned C1>
            static auto backIn(float t) -> float;

            template <unsigned C1>
            static auto backIn2(float t) -> float;

            template <unsigned C1>
            static auto backInOut2(float t) -> float;

            template <unsigned Ondulation>//, unsigned Attenuation>
            static auto elasticOut(float t) -> float;
        };
    };

    template <unsigned C1>
    auto easing::custom::backIn(float t) -> float {
        const float c1 = C1/10.f;
        const float c3 = c1 + 1.f;
        return c3 * t * t * t - c1 * t * t;
    }
    template <unsigned C>
    auto easing::custom::backIn2(float t) -> float {
        const float c = C/10.f;
        return c * t*t - (c - 1.f) * t;
    }
    template <unsigned C>
    auto easing::custom::backInOut2(float t) -> float {
        const float c = C/10.f;
        if (t < 0.5f) {
            return c * (1.4142f*t)*(1.4142f*t) - (c - 1.f) * t;
        }
        t -= 1;
        return -c * (1.4142f*t)*(1.4142f*t) - (c - 1.f) * t + 1;
    }

    template <unsigned Ondulation>
    auto easing::custom::elasticOut(float t) -> float {
        const float ondul = Ondulation / 10.f;
        if (t == 0 || t == 1)
            return t;
        return std::pow(2.f, -10 * t) * std::sin(2 * ns::PI * (ondul * t - 1.25f)) + 1;
    }

}
