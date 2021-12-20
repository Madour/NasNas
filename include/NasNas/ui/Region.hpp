// Created by Modar Nasser on 19/12/2021.

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/core/data/Maths.hpp>

namespace ns::ui {
    struct Region {
        virtual ~Region() = default;
        virtual inline auto getBounds() const -> sf::FloatRect = 0;
        virtual inline auto contains(const sf::Vector2f& pos) const -> bool = 0;
    };

    struct RectangleRegion : public Region {
        float width = 0.f;
        float height = 0.f;

        RectangleRegion(float w, float h) : width(w), height(h) {}

        inline auto getBounds() const -> sf::FloatRect override {
            return {-width/2.f, -height/2.f, width, height};
        }
        inline auto contains(const sf::Vector2f& pos) const -> bool override {
            return getBounds().contains(pos);
        };
    };

    struct CircleRegion : public Region {
        float radius = 0.f;

        CircleRegion(float r) : radius(r) {}

        inline auto getBounds() const -> sf::FloatRect override {
            return {-radius, -radius, 2.f*radius, 2.f*radius};
        }
        inline auto contains(const sf::Vector2f& pos) const -> bool override {
            return norm(pos) < radius;
        };
    };
}
