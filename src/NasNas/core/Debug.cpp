/**
* Created by Modar Nasser on 01/05/2020.
**/

#include "NasNas/core/Debug.hpp"

auto ns::operator<<(std::ostream& os, const sf::Vector2f& vect) -> std::ostream& {
    char b[255];
    sprintf_s(b, "Vector2f(%.3f, %.3f)", vect.x, vect.y);
    os << b;
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::Vector2i& vect) -> std::ostream& {
    os << "Vector2i(" << vect.x << ", " << vect.y << ")";
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::Vector2u& vect) -> std::ostream& {
    os << "Vector2u(" << vect.x << ", " << vect.y << ")";
    return os;
}

auto ns::operator<<(std::ostream& os, const sf::Vector3f& vect) -> std::ostream& {
    char b[255];
    sprintf_s(b, "Vector3(%.3f, %.3f, %.3f)", vect.x, vect.y, vect.z);
    os << b;
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::Vector3i& vect) -> std::ostream& {
    os << "Vector3i(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
    return os;
}

auto ns::operator<<(std::ostream& os, const sf::FloatRect& rect) -> std::ostream& {
    os << "Rect( (" << rect.left << ", " << rect.top << "), (" << rect.width << ", " << rect.height << ") )";
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::IntRect& rect) -> std::ostream& {
    os << "Rect( (" << rect.left << ", " << rect.top << "), (" << rect.width << ", " << rect.height << ") )";
    return os;
}


sf::Color ns::DebugTextInterface::color = sf::Color(255, 255, 255);
sf::Color ns::DebugTextInterface::outline_color = sf::Color(0, 0, 0);
float ns::DebugTextInterface::outline_thickness = 0;
