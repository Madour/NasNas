/**
* Created by Modar Nasser on 01/05/2020.
**/

#include "NasNas/core/Debug.hpp"

using namespace ns;

template<>
void DebugText<int>::update() {
    this->setString(this->variable_name + " " + std::to_string(*this->variable_address));
}

template<>
void DebugText<float>::update() {
    char b[10];
    std::sprintf(b, " %.3f", *this->variable_address);
    this->setString(this->variable_name + b);
}

template<>
void DebugText<sf::Vector2f>::update() {
    char b1[10], b2[10];
    std::sprintf(b1, "(%.3f, ", this->variable_address->x);
    std::sprintf(b2, "%.3f)", this->variable_address->y);
    this->setString(this->variable_name + b1 + b2);
}