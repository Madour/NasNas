// Created by Modar Nasser on 23/10/2021.

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "NasNas/core/data/Rect.hpp"

namespace ns::ui {
    class NineSlice : public sf::Drawable, public sf::Transformable {
    public:
        enum class Mode { Scale, Repeat };

        explicit NineSlice(const sf::Texture& texture, Mode mode=Mode::Scale);
        NineSlice(const sf::Texture& texture, const sf::IntRect& rect, Mode mode=Mode::Scale);

        void setTexture(const sf::Texture& texture);
        void setTextureRect(const sf::IntRect& rect);
        void setSlices(int left, int right, int top, int bottom);

        void setSize(const sf::Vector2i& size);
        void setSize(int width, int height);

        auto getGlobalBounds() const -> sf::FloatRect;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void updateVertices();

        struct Slices {
            ns::FloatRect topleft;
            ns::FloatRect topright;
            ns::FloatRect botleft;
            ns::FloatRect botright;
            ns::FloatRect left;
            ns::FloatRect top;
            ns::FloatRect right;
            ns::FloatRect bot;
            ns::FloatRect center;
        };

        Mode m_mode;
        sf::Vector2f m_size;
        Slices m_texture_slices;
        const sf::Texture* m_texture = nullptr;
        ns::FloatRect m_texture_rect;
        sf::VertexArray m_vertices;
    };
}
