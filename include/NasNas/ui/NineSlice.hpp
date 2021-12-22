// Created by Modar Nasser on 23/10/2021.

#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/core/data/Rect.hpp>

namespace ns::ui {
    class NineSlice : public sf::Drawable, public sf::Transformable {
    public:
        enum class Mode { Stretch, Repeat };

        explicit NineSlice(Mode mode=Mode::Stretch);
        explicit NineSlice(const sf::Texture& texture, Mode mode=Mode::Stretch);
        NineSlice(const sf::Texture& texture, const sf::IntRect& rect, Mode mode=Mode::Stretch);

        void setMode(Mode mode);

        void setTexture(const sf::Texture& texture, bool reset_rect = false);
        void setTextureRect(const sf::IntRect& rect);
        void setSlices(int left, int right, int top, int bottom);

        void setSize(const sf::Vector2i& size);
        void setSize(int width, int height);
        auto getSize() -> const sf::Vector2f&;

        auto getGlobalBounds() const -> sf::FloatRect;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void updateVertices();

        struct Slices {
            enum { CENTER, LEFT, RIGHT, TOP, BOT, TL, TR, BL, BR };
            ns::FloatRect center;
            ns::FloatRect left;
            ns::FloatRect top;
            ns::FloatRect right;
            ns::FloatRect bot;
            ns::FloatRect topleft;
            ns::FloatRect topright;
            ns::FloatRect botleft;
            ns::FloatRect botright;
        };

        Mode m_mode;
        sf::Vector2f m_size;
        Slices m_texture_slices;
        const sf::Texture* m_texture = nullptr;
        ns::FloatRect m_texture_rect;
        sf::VertexArray m_vertices;
    };
}
