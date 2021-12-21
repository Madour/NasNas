// Created by Modar Nasser on 18/07/2021.

#include <NasNas/tween/Easing.hpp>

auto ns::easing::linear(float t) -> float {
    return t;
};

auto ns::easing::quadraticIn(float t) -> float {
    return custom::polynomialIn<2>(t);
};
auto ns::easing::quadraticOut(float t) -> float {
    return custom::polynomialOut<2>(t);
};
auto ns::easing::quadraticInOut(float t) -> float {
    return custom::polynomialInOut<2>(t);
};

auto ns::easing::cubicIn(float t) -> float {
    return custom::polynomialIn<3>(t);
};
auto ns::easing::cubicOut(float t) -> float {
    return custom::polynomialOut<3>(t);
};
auto ns::easing::cubicInOut(float t) -> float {
    return custom::polynomialInOut<3>(t);
};

auto ns::easing::sinusoidalIn(float t) -> float {
    return 1 - std::cos(t * ns::PI / 2.f);
};
auto ns::easing::sinusoidalOut(float t) -> float {
    return std::sin(t * ns::PI / 2.f);
};
auto ns::easing::sinusoidalInOut(float t) -> float {
    return -std::cos(ns::PI * t) / 2.f + 0.5f;
}

auto ns::easing::exponentialIn(float t) -> float {
    if (t == 0) return 0;
    return std::pow(2.f, 10 * t - 10);
}
auto ns::easing::exponentialOut(float t) -> float {
    return 1 - exponentialIn(1 - t);
}
auto ns::easing::exponentialInOut(float t) -> float {
    if (t == 0 || t == 1)
        return t;
    if (t < 0.5f)
        return std::pow(2.f, 20 * t - 10) / 2.f;
    return 1 - std::pow(2.f,-20 * t + 10) / 2.f;
}

auto ns::easing::circularIn(float t) -> float {
    return 1 - std::sqrt(1 - std::pow(t, 2));
}
auto ns::easing::circularOut(float t) -> float {
    return 1 - circularIn(1 - t);
}
auto ns::easing::circularInOut(float t) -> float {
    if (t < 0.5f)
        return 0.5f - std::sqrt(1 - std::pow(2 * t, 2)) / 2.f;
    return 0.5f + std::sqrt(1 - std::pow(-2 * t + 2, 2)) / 2.f;
}

auto ns::easing::bounceIn(float t) -> float {
    return 1.f - bounceOut(1 - t);
}
auto ns::easing::bounceOut(float t) -> float {
    float c = 9.5625f;
    if (t < 1 / 2.75f) {
        return (c - 2.f) * t * t;
    } else if (t < 2.0f / 2.75f) {
        t -= 1.5f / 2.75f;
        return (c - 1.f) * t * t + .75f;
    } else if (t < 2.5f / 2.75f) {
        t -= 2.25f / 2.75f;
        return c * t * t + .9375f;
    } else {
        t -= 2.625f / 2.75f;
        return c * t * t + .984375f;
    }
}
auto ns::easing::bounceInOut(float t) -> float {
    if (t < 0.5f)
        return 0.5f - bounceOut(1 - 2*t) / 2.f;
    else
        return 0.5f + bounceOut(2*t - 1) / 2.f;
}

auto ns::easing::backIn(float t) -> float {
    return custom::backIn<20>(t);
}
auto ns::easing::backOut(float t) -> float {
    return custom::backOut<20>(t);
}
auto ns::easing::backInOut(float t) -> float {
    return custom::backInOut<20>(t);
}

auto ns::easing::backIn2(float t) -> float {
    return custom::backIn2<20>(t);
}
auto ns::easing::backOut2(float t) -> float {
    return custom::backOut2<20>(t);
}
auto ns::easing::backInOut2(float t) -> float {
    return custom::backInOut2<20>(t);
}

auto ns::easing::elasticIn(float t) -> float {
    return custom::elasticIn<25>(t);
}
auto ns::easing::elasticOut(float t) -> float {
    return custom::elasticOut<25>(t);
}
auto ns::easing::elasticInOut(float t) -> float {
    return custom::elasticInOut<25>(t);
}
