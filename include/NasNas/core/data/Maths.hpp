/**
* Created by Modar Nasser on 25/07/2020.
**/


#pragma once

#include <cmath>

#include <SFML/System/Vector2.hpp>

namespace ns {
    constexpr float PI = 3.14159265359f;

    /**
     * \brief Converts a radian angle to degree
     * \param value Radian angle value
     * \return Equivalent degree angle
     */
    inline auto to_degree(float value) -> float {
        return value*(180.f/PI);
    }

    /**
     * \brief Converts a degree angle to radian
     * \param value Degree angle value
     * \return Equivalent radian angle
     */
    inline auto to_radian(float value) -> float {
        return value*(PI/180.f);
    }

    /**
     * \brief Calculates the norm of a vector (its length)
     * \tparam T Vector type
     * \param vector
     * \return Norm of the vector
     */
    template <typename T>
    inline auto norm(const sf::Vector2<T>& vector) -> float {
        return std::sqrt(vector.x*vector.x + vector.y*vector.y);
    }

    /**
     * \brief Calculates the normal of a vector
     * \tparam T Vector type
     * \param vector
     * \return The normal of the vector
     */
    template <typename T>
    inline auto normal(const sf::Vector2<T>& vector) -> sf::Vector2<T> {
        return { -vector.y, vector.x };
    }

    /**
     * \brief Calculates the distance between two points.
     * \tparam T First point coordinates type (int, float or unsigned)
     * \tparam S Second point coordinates type (int, float or unsigned)
     * \param point1
     * \param point2
     * \return The distance between the two points
     */
    template <typename T, typename S>
    inline auto distance(const sf::Vector2<T>& point1, const sf::Vector2<S>& point2) -> float {
        return std::sqrt((point2.x-point1.x)*(point2.x-point1.x) + (point2.y-point1.y)*(point2.y-point1.y));
    }

    template <typename T>
    inline auto dot_product(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) -> T {
        return v1.x * v2.x + v1.y * v2.y;
    }

    template <typename T>
    inline auto cross_product(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) -> T {
        return v1.x * v2.y - v1.y * v2.x;
    }

    /**
     * \brief Returns the clockwise positive angle of a vector
     * \tparam T Vector type
     * \param vector
     * \return The angle between (-PI; PI]
     */
    template <typename T>
    inline auto angle(const sf::Vector2<T>& vector) -> float {
        return std::atan2(vector.y, vector.x);
    }

    /**
     * \brief Returns the clockwise positive angle between two vectors
     * \tparam T Vector type
     * \param v1
     * \param v2
     * \return The angle between (-PI; PI]
     */
    template <typename T>
    inline auto angle(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) -> float {
        auto r = std::atan2(v2.y, v2.x) - std::atan2(v1.y, v1.x);
        return (std::abs(r) > PI ? r - 2*PI*r/std::abs(r) : r);
    }

    /**
     * \brief Does element wise multiplication between two vectors
     * \tparam T Vector type (int, float or unsigned)
     * \param v1
     * \param v2
     * \return Returns {v1.x * v2.x, v1.y * v2.y}
     */
    template <typename T>
    inline auto operator*(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2) -> sf::Vector2<T> {
        return {v1.x*v2.x, v1.y*v2.y};
    }
}
