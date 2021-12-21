// Created by Modar Nasser on 20/04/2021.

#include <NasNas/core/graphics/Transformable.hpp>

using namespace ns;

void Transformable::setPosition(float x, float y) {
    changed = true;
    sf::Transformable::setPosition(x, y);
}

void Transformable::setPosition(const sf::Vector2f& position) {
    changed = true;
    sf::Transformable::setPosition(position);
}

void Transformable::setRotation(float angle) {
    changed = true;
    sf::Transformable::setRotation(angle);
}

void Transformable::setScale(float factorX, float factorY) {
    changed = true;
    sf::Transformable::setScale(factorX, factorY);
}

void Transformable::setScale(const sf::Vector2f& factors) {
    changed = true;
    sf::Transformable::setScale(factors);
}

void Transformable::setOrigin(float x, float y) {
    changed = true;
    sf::Transformable::setOrigin(x, y);
}

void Transformable::setOrigin(const sf::Vector2f& origin) {
    changed = true;
    sf::Transformable::setOrigin(origin);
}

void Transformable::move(float offsetX, float offsetY) {
    changed = true;
    sf::Transformable::move(offsetX, offsetY);
}

void Transformable::move(const sf::Vector2f& offset) {
    changed = true;
    sf::Transformable::move(offset);
}

void Transformable::rotate(float angle) {
    changed = true;
    sf::Transformable::rotate(angle);
}

void Transformable::scale(float factorX, float factorY) {
    changed = true;
    sf::Transformable::scale(factorX, factorY);
}

void Transformable::scale(const sf::Vector2f& factor) {
    changed = true;
    sf::Transformable::scale(factor);
}

