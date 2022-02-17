// Created by Modar Nasser on 17/02/2022.

#pragma once

#include <map>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

#include <NasNas/core/data/Rect.hpp>

namespace ns {

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

}
