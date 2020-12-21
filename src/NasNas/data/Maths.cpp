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

}
