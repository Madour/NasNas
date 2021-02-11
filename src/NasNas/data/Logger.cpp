/**
* Created by Modar Nasser on 21/04/2020.
**/

#include <iomanip>
#include "NasNas/data/Logger.hpp"

using namespace ns;

auto sf::operator<<(std::ostream& os, const sf::Vector2f& vect) -> std::ostream& {
    os << "Vec2d(" << std::setprecision(6) << vect.x << ", " << vect.y << ")";
    return os;
}
auto sf::operator<<(std::ostream& os, const sf::Vector2i& vect) -> std::ostream& {
    os << "Vec2d(" << vect.x << ", " << vect.y << ")";
    return os;
}
auto sf::operator<<(std::ostream& os, const sf::Vector2u& vect) -> std::ostream& {
    os << "Vec2d(" << vect.x << ", " << vect.y << ")";
    return os;
}

auto sf::operator<<(std::ostream& os, const sf::Vector3f& vect) -> std::ostream& {
    os << "Vec3d(" << std::setprecision(6) << vect.x << ", " << vect.y << ", " << vect.z << ")";
    return os;
}
auto sf::operator<<(std::ostream& os, const sf::Vector3i& vect) -> std::ostream& {
    os << "Vec3d(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
    return os;
}

auto sf::operator<<(std::ostream& os, const sf::FloatRect& rect) -> std::ostream& {
    os << "Rect((" << std::setprecision(6) << rect.left << ", " << rect.top << "), (" << rect.width << ", " << rect.height << "))";
    return os;
}
auto sf::operator<<(std::ostream& os, const sf::IntRect& rect) -> std::ostream& {
    os << "Rect((" << rect.left << ", " << rect.top << "), (" << rect.width << ", " << rect.height << "))";
    return os;
}

auto sf::operator<<(std::ostream& os, const sf::Color& color) -> std::ostream& {
    os << "rgba(" << (int)color.r << ", " << (int)color.g << ", " << (int)color.b << ", " << (int)color.a << ")";
    return os;
}

void Logger::logr() { std::cout << std::endl; }
