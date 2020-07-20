/**
* Created by Modar Nasser on 21/04/2020.
**/


#include "NasNas/core/Logger.hpp"

using namespace ns;

auto ns::operator<<(std::ostream& os, const sf::Vector2f& vect) -> std::ostream& {
    char b[255];
    sprintf(b, "Vector(%.3f, %.3f)", vect.x, vect.y);
    os << b;
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::Vector2i& vect) -> std::ostream& {
    os << "Vector(" << vect.x << ", " << vect.y << ")";
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::Vector2u& vect) -> std::ostream& {
    os << "Vector(" << vect.x << ", " << vect.y << ")";
    return os;
}

auto ns::operator<<(std::ostream& os, const sf::Vector3f& vect) -> std::ostream& {
    char b[255];
    sprintf(b, "Vector(%.3f, %.3f, %.3f)", vect.x, vect.y, vect.z);
    os << b;
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::Vector3i& vect) -> std::ostream& {
    os << "Vector(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
    return os;
}

auto ns::operator<<(std::ostream& os, const sf::FloatRect& rect) -> std::ostream& {
    char b[255];
    sprintf(b,  "Rect((%.3f, %.3f), (%.3f, %.3f))", rect.left, rect.top, rect.width, rect.height);
    os << b;
    return os;
}
auto ns::operator<<(std::ostream& os, const sf::IntRect& rect) -> std::ostream& {
    os << "Rect((" << rect.left << ", " << rect.top << "), (" << rect.width << ", " << rect.height << "))";
    return os;
}

auto ns::operator<<(std::ostream& os, const sf::Color& color) -> std::ostream& {
    os << "rgba(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << (int)color.a << ")";
    return os;
}

void Logger::logr() { std::cout << std::endl; }
