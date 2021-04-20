// Created by Modar Nasser on 20/04/2021.

#pragma once

#include <SFML/Graphics.hpp>
#include "NasNas/core/graphics/Drawable.hpp"

namespace ns {
    class Sprite : public DrawableTransformable {
    public:
        Sprite() = default;
        explicit Sprite(const sf::Sprite& other);
        explicit Sprite(const sf::Texture& texture);
        Sprite(const sf::Texture& texture, const sf::IntRect& rectangle);

        void setTexture(const sf::Texture& texture, bool reset_rect = false);
        void setTextureRect(const sf::IntRect& rectangle);

        void setColor(const sf::Color& color);
        void setColor(const sf::Color& color, unsigned vert_index);

        auto getTexture() const -> const sf::Texture*;
        auto getTextureRect() const -> const IntRect&;

        auto getColor() const -> const sf::Color&;
        auto getColor(unsigned vert_index) const -> const sf::Color&;

        auto getVertex(unsigned index) const -> const sf::Vertex&;

        auto getLocalBounds() const -> ns::FloatRect;
        auto getGlobalBounds() const -> ns::FloatRect override;

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Vertex m_vertices[4];
        const sf::Texture* m_texture = nullptr;
        ns::IntRect m_texture_rect;
    };
}
