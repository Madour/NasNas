/**
* Created by Modar Nasser on 01/05/2020.
**/

#include "NasNas/core/Debug.hpp"

using namespace ns;

template<>
void DebugText<int>::update() {
    if (this->variable_address != nullptr)
        this->setString(this->label + " " + std::to_string(*this->variable_address));
    else
        this->setString(this->label + " " + std::to_string((this->method_address)(*this->object_address)));
}

template<>
void DebugText<float>::update() {
    char b[255];
    if (this->variable_address != nullptr) {
        std::sprintf(b, " %.3f", *this->variable_address);
    }
    else {
        std::sprintf(b, " %.3f", (this->method_address)(*this->object_address));
    }
    this->setString(this->label + b);
}

template<>
void DebugText<sf::Vector2f>::update() {
    char b1[255], b2[255];
    if (this->variable_address != nullptr) {
        std::sprintf(b1, " (%.3f, ", this->variable_address->x);
        std::sprintf(b2, "%.3f)", this->variable_address->y);
    }
    else {
        sf::Vector2f val = (this->method_address)(*this->object_address);
        std::sprintf(b1, " (%.3f, ", val.x);
        std::sprintf(b2, "%.3f)", val.y);
    }
    this->setString(this->label + b1 + b2);
}

template<>
void DebugText<std::string>::update() {
    if (this->variable_address != nullptr)
        this->setString(this->label + " " + *this->variable_address);
    else
        this->setString(this->label + " " + (this->method_address)(*this->object_address));
}
