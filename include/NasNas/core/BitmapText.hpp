/**
* Created by Modar Nasser on 25/06/2020.
**/


#pragma once

#include <memory>

#include "SFML/Graphics.hpp"
#include "NasNas/data/Rect.hpp"
#include "NasNas/data/AppComponent.hpp"

namespace ns {
    class BitmapFont;

    class BitmapGlyph {
    public:
        const IntRect texture_rect;
        const char character;
        const int advance;

    private:
        friend BitmapFont;
        BitmapGlyph(const IntRect& texture_rect, char character, int spacing);
    };

    class BitmapFont {
    public:
        BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size);
        BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size, const std::string& chars_map);
        BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size, const std::unordered_map<char, int>& advance_map);
        BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size, const std::string& chars_map, const std::unordered_map<char, int>& advance_map);

        ~BitmapFont();

        auto getTexture() -> const sf::Texture*;
        auto getGlyphSize() -> const sf::Vector2i&;
        auto getGlyph(char character) -> const BitmapGlyph&;

    private:
        const sf::Texture* m_texture;
        sf::Vector2i m_glyph_size;
        std::string m_chars_map;
        std::unordered_map<char, int> m_advance_map;
        std::unordered_map<char, BitmapGlyph*> m_glyphs;
    };

    class BitmapText : public Drawable{
    public:
        explicit BitmapText(const std::string& text);
        BitmapText(const std::string& text, const std::shared_ptr<BitmapFont>& font);

        void setFont(const std::shared_ptr<BitmapFont>& font);

        void move(float offsetx, float offsety) override;

        auto getPosition() -> sf::Vector2f override;
        void setPosition(const sf::Vector2f& position);

        auto getGlobalBounds() -> ns::FloatRect override;

        auto getWidth() -> int;
        auto getHeight() -> int;
        auto getSize() -> sf::Vector2f;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        std::string m_text;
        sf::Transformable m_transformable;
        std::shared_ptr<BitmapFont> m_font = nullptr;
        sf::VertexArray m_sprite;
    };

}
