/**
* Created by Modar Nasser on 20/04/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <iomanip>

namespace ns {
    /** Extending sf::Rect with customized properties / shortcuts
     *
     * @tparam T : Type of the Rect (int or float)
     */
    template <typename T>
    class Rect: public sf::Rect<T> {
    public:
        // parent constructor
        using sf::Rect<T>::Rect;
        // copy constructor
        Rect<T>(const Rect<T> &rect);

        auto repr() const -> std::string;

        sf::Vector2<T> size = sf::Vector2<T>(this->width, this->height);

        T right = this->left + this->width;

        T bottom = this->top + this->height;

        sf::Vector2<T> topleft = sf::Vector2<T>(this->left, this->top);
        sf::Vector2<T> topright = sf::Vector2<T>(this->right, this->top);
        sf::Vector2<T> bottomleft = sf::Vector2<T>(this->left, this->bottom);
        sf::Vector2<T> bottomright = sf::Vector2<T>(this->right, this->bottom);

        sf::Vector2f center =sf::Vector2f((float)this->width/2.0, (float)this->height/2.0);

        template <typename S>
        friend auto operator<< (std::ostream& os, const Rect<S>& rect) -> std::ostream& ;
    };

    template<typename T>
    Rect<T>::Rect(const Rect<T> &rect):sf::Rect<T>(rect) {
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

