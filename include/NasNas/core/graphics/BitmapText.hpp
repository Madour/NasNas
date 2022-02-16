/**
* Created by Modar Nasser on 25/06/2020.
**/


#pragma once

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <SFML/System/String.hpp>

#include <NasNas/core/data/Rect.hpp>

namespace ns {

    class BitmapFont;

    struct BitmapGlyph {
        ns::IntRect texture_rect; ///< BitmapGlyph rectangle on the BitmapFont texture
        wchar_t character;        ///< Character represented by the BitmapGlyph
        unsigned advance;         ///< Space to add after the BitmapGlyph
    };

    /**
     * \brief A font that can be created from a texture
     */
    class BitmapFont {
        static constexpr wchar_t default_characters[] = L" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    public:
        BitmapFont() = default;

        /**
         * \brief Creates a BitmapFont from a Texture
         *
         * \param texture Font texture
         * \param glyph_size Glyphs size in pixels
         */
        void loadFromTexture(const sf::Texture& texture, const sf::Vector2u& glyph_size, unsigned advance);

        /**
         * \brief Get BitmapFont texture
         *
         * \return Const pointer to the Texture
         */
        auto getTexture() const -> const sf::Texture*;

        /**
         * \brief Get BitmapFont glyph size
         *
         * \return Glyph size
         */
        auto getGlyphSize() const -> const sf::Vector2u&;

        void setCharacters(const std::wstring& characters);

        void setCharactersAdvance(const std::map<std::wstring, unsigned>& advances);

        /**
         * \brief Get the BitmapGlyph data of a given character

         * \param character A character of the font.
         *
         * \return BitmapGlyph data of the character
         */
        auto getGlyph(wchar_t character) const -> const BitmapGlyph&;

        auto computeStringSize(const std::wstring& string) const -> sf::Vector2i;

    private:
        const sf::Texture* m_texture = nullptr;
        sf::Vector2u m_glyph_size;
        unsigned m_default_advance = 0;
        std::unordered_map<wchar_t, BitmapGlyph> m_glyphs;
    };

    /**
     * \brief A BitmapText is a Drawable that uses a BitmapFont to display text.
     */
    class BitmapText : public sf::Drawable, public sf::Transformable {
    public:
        BitmapText();

        /**
         * \brief Creates a BitmapText
         *
         * \param string String to display
         * \param font Font used to draw the string
         */
        BitmapText(const sf::String& string, const ns::BitmapFont& font);

        /**
         * \brief Set the text's string
         *
         * \param string New string
         */
        void setString(const sf::String& string);

        auto getString() -> const sf::String&;

        /**
         * \brief Set the text's BitmapFont
         *
         * \param font New bitmapfont
         */
        void setFont(const BitmapFont& font);

        auto getFont() const -> const BitmapFont*;

        /**
         * \brief Set the font color
         *
         * \param color The color
         */
        void setColor(const sf::Color& color);

        auto getColor() const -> const sf::Color&;

        void setLetterSpacing(float factor);

        auto getLetterSpacing() const -> float;

        void setLineSpacing(float factor);

        auto getLineSpacing() const -> float;

        /**
         * \brief Get BitmapText position
         * \return Position
         */
        auto getPosition() const -> sf::Vector2f;

        /**
         * \brief Get BitmapText size
         * \return Size
         */
        auto getSize() const -> sf::Vector2f;

        /**
         * \brief Get BitmapText local bounds
         * \return Local bounds rectangle
         */
        auto getLocalBounds() const -> ns::FloatRect;

        /**
         * \brief Get BitmapText global bounds
         * \return Global bounds rectangle
         */
        auto getGlobalBounds() const -> ns::FloatRect;

    private:
        void updateVertices() const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::String m_string;
        const BitmapFont* m_font = nullptr;
        sf::Color m_color = sf::Color::White;

        float m_letter_spacing = 1.f;
        float m_line_spacing = 1.f;

        mutable sf::Vector2f m_size;
        mutable sf::VertexArray m_vertices;
        mutable bool m_need_update;
    };

}
