// Created by Modar Nasser on 20/04/2021.

#pragma once

#include <SFML/Graphics/Transformable.hpp>

namespace ns {
    class SpriteBatch;
    class Sprite;
    class Scene;

    class Transformable : sf::Transformable {
    public:
        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& position);

        void setRotation(float angle);

        void setScale(float factorX, float factorY);
        void setScale(const sf::Vector2f& factors);

        void setOrigin(float x, float y);
        void setOrigin(const sf::Vector2f& origin);

        void move(float offsetX, float offsetY);
        void move(const sf::Vector2f& offset);

        void rotate(float angle);

        void scale(float factorX, float factorY);
        void scale(const sf::Vector2f& factor);

        using sf::Transformable::getPosition;
        using sf::Transformable::getRotation;
        using sf::Transformable::getScale;
        using sf::Transformable::getOrigin;
        using sf::Transformable::getTransform;
        using sf::Transformable::getInverseTransform;

    private:
        friend SpriteBatch;
        friend Sprite;
        friend Scene;
        mutable bool changed = true;

    };
}

