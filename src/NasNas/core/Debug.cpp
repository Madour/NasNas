/**
* Created by Modar Nasser on 01/05/2020.
**/

#include "NasNas/core/Debug.hpp"

using namespace ns;

template<>
void DebugText<int>::update() {
    if (m_variable_address != nullptr)
        setString(m_label + " " + std::to_string(*m_variable_address));
    else
        setString(m_label + " " + std::to_string((m_method_address)(*m_object_address)));
}

template<>
void DebugText<float>::update() {
    char b[255];
    if (m_variable_address != nullptr) {
        std::sprintf(b, " %.3f", *m_variable_address);
    }
    else {
        std::sprintf(b, " %.3f", (m_method_address)(*m_object_address));
    }
    setString(m_label + b);
}

template<>
void DebugText<sf::Vector2f>::update() {
    char b1[255], b2[255];
    if (m_variable_address != nullptr) {
        std::sprintf(b1, " (%.3f, ", m_variable_address->x);
        std::sprintf(b2, "%.3f)", m_variable_address->y);
    }
    else {
        sf::Vector2f val = (m_method_address)(*m_object_address);
        std::sprintf(b1, "(%.3f, ", val.x);
        std::sprintf(b2, "%.3f)", val.y);
    }
    setString(m_label + b1 + b2);
}

template<>
void DebugText<std::string>::update() {
    if (m_variable_address != nullptr)
        setString(m_label + " " + *m_variable_address);
    else
        setString(m_label + " " + (m_method_address)(*m_object_address));
}
