/**
* Created by Modar Nasser on 25/07/2020.
**/


#pragma once

#include <cmath>
#include <SFML/System.hpp>

namespace ns {
    const float PI = std::acos(-1.f);

    /**
     * \brief Converts a radian angle to degree
     * \param value Radian angle value
     * \return Equivalent degree angle
     */
    auto to_degree(float value) -> float;

    /**
     * \brief Converts a degree angle to radian
     * \param value Degree angle value
     * \return Equivalent radian angle
     */
    auto to_radian(float value) -> float;

    /**
     * \brief Calculates the dot product between two vectors
     * \tparam T First vector type (int, float or unsigned)
     * \tparam S Second vector type (int, float or unsigned)
     * \param vector1
     * \param vector2
     * \return Dot product between the two vectors
     */
    template <typename T, typename S>
    float operator*(const sf::Vector2<T>& vector1, const sf::Vector2<S>& vector2);

    /**
     * \brief Calculates the norm of a vector (its length)
     * \tparam T Vector type
     * \param vector
     * \return Norm of the vector
     */
    template <typename T>
    inline auto norm(const sf::Vector2<T>& vector) -> float {
        return std::hypot(vector.x, vector.y);
    }

    /**
     * \brief Calculates the normal of a vector
     * \tparam T Vector type
     * \param vector
     * \return The normal of the vector
     */
    template <typename T>
    inline auto normal(const sf::Vector2<T>& vector) -> sf::Vector2f {
        return { -vector.x, vector.y };
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
        return std::hypot(point2.x - point1.x, point2.y - point1.y);
    }
}
