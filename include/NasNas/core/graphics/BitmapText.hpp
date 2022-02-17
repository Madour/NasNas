// Created by Modar Nasser on 25/06/2020.

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
