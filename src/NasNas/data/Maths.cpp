/**
* Created by Modar Nasser on 25/07/2020.
**/


#include "NasNas/data/Maths.hpp"

namespace ns {

    auto to_degree(float value) -> float {
        //while (std::abs(value) > 2*PI)
        //    value -= (2*PI)*(value/std::abs(value));
        return value*(180.f/PI);
    }

    auto to_radian(float value) -> float {
        //while (std::abs(value) > 360)
        //    value -= (360.f)*(value/std::abs(value));
        return value*(PI/180.f);
    }

    template <typename T, typename S>
    float operator*(const sf::Vector2<T>& vector1, const sf::Vector2<S>& vector2) {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

}
