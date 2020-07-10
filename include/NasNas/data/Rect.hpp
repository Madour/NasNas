/**
* Created by Modar Nasser on 20/04/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <iomanip>

namespace ns {
    /**
     * \brief Extending sf::Rect with customized properties
     *
     * \tparam T : Type of the Rect (int or float)
     */
    template <typename T>
    class Rect: public sf::Rect<T> {
    public:
        // parent constructor
        using sf::Rect<T>::Rect;
        // copy constructor
        Rect<T>(const Rect<T> &rect);

        Rect<T>(const sf::Rect<T>& rect);

        auto repr() const -> std::string;

        sf::Vector2<T> size() const { return sf::Vector2<T>(this->width, this->height); }

        T right() const { return this->left + this->width; }

        T bottom() const { return this->top + this->height; }

        sf::Vector2<T> topleft() const { return sf::Vector2<T>(this->left, this->top); }
        sf::Vector2<T> topright() const { return sf::Vector2<T>(right(), this->top); }
        sf::Vector2<T> bottomleft() const { return sf::Vector2<T>(this->left, bottom()); }
        sf::Vector2<T> bottomright() const { return sf::Vector2<T>(right(), bottom()); }

        sf::Vector2f center() const { return sf::Vector2f((float)this->width/2.f, (float)this->height/2.f); }

        template <typename S>
        friend auto operator<< (std::ostream& os, const Rect<S>& rect) -> std::ostream& ;
    };

    template<typename T>
    Rect<T>::Rect(const Rect<T> &rect): sf::Rect<T>(rect) {
    }

    template <typename T>
    Rect<T>::Rect(const sf::Rect<T>& rect): sf::Rect<T>(rect) {
    }

    template <typename T>
    auto Rect<T>::repr() const -> std::string {
        std::string s_left = std::to_string(this->left);
        std::string s_top = std::to_string(this->top);
        std::string s_width = std::to_string(this->width);
        std::string s_height = std::to_string(this->height);
        return std::string("Rect(("+ s_left +", "+ s_top +"), ("+ s_width +", "+ s_height +"))" );
    }

    template <typename T>
    auto operator<<(std::ostream& os, const Rect<T>& rect) -> std::ostream& {
        os << rect.repr();
        return os;
    }

    typedef Rect<int> IntRect;
    typedef Rect<float> FloatRect;
}

