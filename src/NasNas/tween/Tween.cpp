// Created by Modar Nasser on 17/07/2021.

#include "NasNas/tween/Tween.hpp"

using namespace ns;
using namespace ns::tween;

auto Tween::from(float f) -> Tween& {
    m_from = f;
    return *this;
}