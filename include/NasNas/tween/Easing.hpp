// Created by Modar Nasser on 18/07/2021.

#pragma once

#include <functional>

namespace ns {

    namespace tween {
        using EasingFunction = std::function<float(float)>;
        using CallbackFunction = std::function<void(float)>;
    }

    struct easing {
        static auto linear(float t) -> float;

        static auto quadraticIn(float t) -> float;
        static auto quadraticOut(float t) -> float;
        static auto quadraticInOut(float t) -> float;

        static auto cubicIn(float t) -> float;
        static auto cubicOut(float t) -> float;
        static auto cubicInOut(float t) -> float;

        static auto sinusoidalIn(float t) -> float;
        static auto sinusoidalOut(float t) -> float;
        static auto sinusoidalInOut(float t) -> float;

        static auto exponentialIn(float t) -> float;
        static auto exponentialOut(float t) -> float;
        static auto exponentialInOut(float t) -> float;

        static auto circularIn(float t) -> float;
        static auto circularOut(float t) -> float;
        static auto circularInOut(float t) -> float;

        static auto bounceIn(float t) -> float;
        static auto bounceOut(float t) -> float;
        static auto bounceInOut(float t) -> float;

        static auto backIn(float t) -> float;
        static auto backOut(float t) -> float;
        static auto backInOut(float t) -> float;

        static auto backIn2(float t) -> float;
        static auto backOut2(float t) -> float;
        static auto backInOut2(float t) -> float;

        static auto elasticIn(float t) -> float;
        static auto elasticOut(float t) -> float;
        static auto elasticInOut(float t) -> float;

        struct custom {
            template <unsigned Degree> static auto polynomialIn(float t) -> float;
            template <unsigned Degree> static auto polynomialOut(float t) -> float;
            template <unsigned Degree> static auto polynomialInOut(float t) -> float;

            template <unsigned Pull> static auto backIn(float t) -> float;
            template <unsigned Pull> static auto backOut(float t) -> float;
            template <unsigned Pull> static auto backInOut(float t) -> float;

            template <unsigned Pull> static auto backIn2(float t) -> float;
            template <unsigned Pull> static auto backOut2(float t) -> float;
            template <unsigned Pull> static auto backInOut2(float t) -> float;

            template <unsigned Ondulation> static auto elasticIn(float t) -> float;
            template <unsigned Ondulation> static auto elasticOut(float t) -> float;
            template <unsigned Ondulation> static auto elasticInOut(float t) -> float;
        };
    };
}

#include "NasNas/tween/Easing.tpp"

