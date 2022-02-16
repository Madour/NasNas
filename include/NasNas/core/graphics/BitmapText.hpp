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
        auto getTexture() -> const sf::Texture*;

        /**
         * \brief Get BitmapFont glyph size
         *
         * \return Glyph size
         */
        auto getGlyphSize() -> const sf::Vector2u&;

        void setCharacters(const std::wstring& characters);

        void setCharactersAdvance(const std::map<std::wstring, unsigned>& advances);

        /**
         * \brief Get the BitmapGlyph data of a given character

         * \param character A character of the font.
         *
         * \return BitmapGlyph data of the character
         */
        auto getGlyph(wchar_t character) -> const BitmapGlyph&;

        auto computeStringSize(const std::wstring& string) -> sf::Vector2i;

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
        /**
         * \brief Creates a BitmapText
         *
         * When using this constructor, you have to manually set the font used by
         * calling `setFont`.
         *
         * \param text String to display
         */
        explicit BitmapText(const std::wstring& text, ns::BitmapFont* font=nullptr);

        auto getString() -> const std::wstring&;

        /**
         * \brief Set a the string to be displayed
         *
         * \param string String to write
         */
        void setString(const std::wstring& string);

        auto getFont() -> BitmapFont*;

        /**
         * \brief Set the BitmapFont to use

         * \param font BitmapFont to use
         */
        void setFont(const std::shared_ptr<BitmapFont>& font);

        /**
         * \brief Set the BitmapFont to use

         * \param font BitmapFont to use
         */
         void setFont(BitmapFont* font);

        /**
         * \brief Set the font color
         *
         * \param color The color
         */
        void setColor(const sf::Color& color);

        /**
         * \brief Get BitmapText position
         * \return Position
         */
        auto getPosition() const -> sf::Vector2f;

        /**
         * \brief Get BitmapText global bounds
         * \return Global bounds rectangle
         */
        auto getGlobalBounds() const -> ns::FloatRect;

        /**
         * \brief Set the maximum width of the Text.
         * Line breaks will be inserted to respect the max width value
         * \param max_width
         */
        virtual void setMaxWidth(int max_width);

        /**
         * \brief Get BitmapText size
         * \return Size
         */
        auto getSize() const -> sf::Vector2f;

    protected:
        auto getProcessedString() -> const std::wstring&;
        void processString();

    private:
        void updateVertices();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        std::wstring m_string;
        std::wstring m_processed_string;
        BitmapFont* m_font = nullptr;
        sf::Color m_color = sf::Color::White;

        int m_max_width = 0;
        int m_width = 0;
        int m_height = 0;

        sf::Transformable m_transformable;
        sf::VertexArray m_vertices;
    };

}
