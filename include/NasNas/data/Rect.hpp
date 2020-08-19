/**
* Created by Modar Nasser on 20/04/2020.
**/


#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

namespace ns {
    /**
     * \brief Extending sf::Rect with customized properties
     *
     * \tparam T : Type of the Rect (int or float)
     */
    template <typename T>
    class Rect : public sf::Rect<T> {
    public:
        // parent constructor
        using sf::Rect<T>::Rect;
        // copy constructor
        Rect(const ns::Rect<T>& rect);

        template <typename S>
        explicit Rect(const sf::Rect<S>& rect);

        auto size() const -> sf::Vector2<T> { return sf::Vector2<T>(this->width, this->height); }

        auto right() const -> T { return this->left + this->width; }

        auto bottom() const -> T { return this->top + this->height; }

        auto topleft() const -> sf::Vector2<T> { return sf::Vector2<T>(this->left, this->top); }
        auto topright() const -> sf::Vector2<T> { return sf::Vector2<T>(right(), this->top); }
        auto bottomleft() const -> sf::Vector2<T> { return sf::Vector2<T>(this->left, bottom()); }
        auto bottomright() const -> sf::Vector2<T> { return sf::Vector2<T>(right(), bottom()); }

        auto center() const -> sf::Vector2f { return sf::Vector2f((float)this->width/2.f, (float)this->height/2.f); }

        auto operator=(const ns::Rect<T>& other) -> ns::Rect<T>&;

        template <typename S>
        auto operator=(const sf::Rect<S>& other) -> ns::Rect<T>&;

    };

    template <typename T>
    Rect<T>::Rect(const ns::Rect<T>& rect): sf::Rect<T>(rect)
    {}

    template <typename T>
    template <typename S>
    Rect<T>::Rect(const sf::Rect<S>& rect) : sf::Rect<T>(rect)
    {}

    template <typename T>
    auto Rect<T>::operator=(const ns::Rect<T> &other) -> ns::Rect<T>&{
        if (&other == this)
            return *this;
        this->left = other.left;
        this->top = other.top;
        this->width = other.width;
        this->height = other.height;
        return *this;
    }

    template <typename T>
    template <typename S>
    auto Rect<T>::operator=(const sf::Rect<S>& other) -> ns::Rect<T>& {
        this->left = static_cast<T>(other.left);
        this->top = static_cast<T>(other.top);
        this->width = static_cast<T>(other.width);
        this->height = static_cast<T>(other.height);
        return *this;
    }

    typedef Rect<int> IntRect;
    typedef Rect<float> FloatRect;

}
