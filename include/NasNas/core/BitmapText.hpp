/**
* Created by Modar Nasser on 25/06/2020.
**/


#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "NasNas/data/Drawable.hpp"
#include "NasNas/data/Rect.hpp"

namespace ns {

    class BitmapFont;

    class BitmapGlyph {
    public:
        const ns::IntRect texture_rect; ///< BitmapGlyph rectangle on the BitmapFont texutre
        const char character;           ///< Character represented by the BitmapGlyph
        const int advance;              ///< Space to add after the BitmapGlyph

    private:
        friend BitmapFont;

        /**
         * \brief Creates a BitmapGlyph
         *
         * \param texture_rect BitmapGlyph rectangle on the BitmapFont texutre
         * \param character Character represented by the BitmapGlyph
         * \param spacing Space to add after the BitmapGlyph
         */
        BitmapGlyph(const ns::IntRect& texture_rect, char character, int spacing);
    };

    /**
     * \brief A font that can be created from a texture
     */
    class BitmapFont {
    public:
        /**
         * \brief Creates a BitmapFont from a Texture
         *
         * This constructor will use the default character map and advance map.
         * Make sure your characters in the texture are placed in the following order (first character is a space):
         *  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~
         *
         * \param texture Font texture
         * \param glyph_size Glyphs size in pixels
         */
        BitmapFont(const sf::Texture& texture, const sf::Vector2u& glyph_size);

        /**
         * \brief Creates a BitmapFont from a Texture
         *
         * This constructor will use the provided character map.
         *
         * \param texture Font texture
         * \param glyph_size Glyphs size in pixels
         * \param chars_map Character map, defines the order of the characters on the texture
         */
        BitmapFont(const sf::Texture& texture, const sf::Vector2u& glyph_size, const std::string& chars_map);

        /**
        * \brief Creates a BitmapFont from a Texture
        *
        * This constructor will use the provided advance map and the default character map.
        * Make sure your characters in the texture are placed in the following order (first character is a space):
        *  !"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~
        *
        * \param texture Font texture
        * \param glyph_size Glyphs size in pixels
        * \param advance_map Advance map, defines the space after each character
        */
        BitmapFont(const sf::Texture& texture, const sf::Vector2u& glyph_size, const std::unordered_map<char, int>& advance_map);

        /**
         * \brief Creates a BitmapFont from a Texture
         *
         * \param texture Font texture
         * \param glyph_size Glyphs size in pixels
         * \param chars_map Character map, defines the order of the characters on the texture
         * \param advance_map Advance map, defines the space after each character
         */
        BitmapFont(const sf::Texture& texture, const sf::Vector2u& glyph_size, const std::string& chars_map, const std::unordered_map<char, int>& advance_map);

        ~BitmapFont();

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

        /**
         * \brief Get the BitmapGlyph data of a given character

         * \param character A character of the font.
         *
         * \return BitmapGlyph data of the character
         */
        auto getGlyph(char character) -> const BitmapGlyph&;

        auto computeStringSize(const std::string& string) -> sf::Vector2i;

    private:
        const sf::Texture* m_texture;
        const sf::Vector2u m_glyph_size;
        std::string m_chars_map;
        std::unordered_map<char, int> m_advance_map;
        std::unordered_map<char, BitmapGlyph*> m_glyphs;
    };

    /**
     * \brief A BitmapText is a Drawable that uses a BitmapFont to display text.
     */
    class BitmapText : public ns::Drawable {
    public:
        /**
         * \brief Creates a BitmapText
         *
         * When using this constructor, you have to manually set the font used by
         * calling `setFont`.
         *
         * \param text String to display
         */
        explicit BitmapText(const std::string& text);

        auto getString() -> const std::string&;

        /**
         * \brief Set a the string to be displayed
         *
         * \param string String to write
         */
        void setString(const std::string& string);

        auto getFont() -> std::shared_ptr<BitmapFont>&;

        /**
         * \brief Set the BitmapFont to use

         * \param font BitmapFont to use
         */
        void setFont(const std::shared_ptr<BitmapFont>& font);

        /**
         * \brief Set the font color
         *
         * \param color The color
         */
        void setColor(const sf::Color& color);

        /**
         * \brief Move the BitmapText
         *
         * \param offsetx X position offset
         * \param offsety Y position offset
         */
        void move(float offsetx, float offsety);

        /**
         * \brief Get BitmapText position
         * \return Position
         */
        auto getPosition() -> sf::Vector2f override;

        /**
         * \brief Set BitmapText position
         * \param position New position
         */
        void setPosition(const sf::Vector2f& position);

        /**
         * \brief St BitmapText Position
         * \param x X coordinate
         * \param y Y coordinate
         */
        void setPosition(float x, float y);

        /**
         * \brief Get BitmapText global bounds
         * \return Global bounds rectangle
         */
        auto getGlobalBounds() -> ns::FloatRect override;

        /**
         * \brief Set the maximum width of the Text.
         * Line breaks will be inserted to respect the max width value
         * \param max_width
         */
        virtual void setMaxWidth(int max_width);

        /**
         * \brief Get BitmapText width
         * \return Width
         */
        auto getWidth() const -> int;
        /**
         * \brief Get BitmapText height
         * \return Height
         */
        auto getHeight() const -> int;
        /**
         * \brief Get BitmapText size
         * \return Size
         */
        auto getSize() const -> sf::Vector2f;

    protected:
        auto getProcessedString() -> const std::string&;
        void processString();

    private:
        void updateVertices();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        std::string m_string;
        std::string m_processed_string;
        std::shared_ptr<BitmapFont> m_font = nullptr;
        sf::Color m_color = sf::Color::White;

        int m_max_width = 0;
        int m_width = 0;
        int m_height = 0;

        sf::Transformable m_transformable;
        sf::VertexArray m_vertices;
    };

}
