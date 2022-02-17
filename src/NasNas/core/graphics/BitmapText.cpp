// Created by Modar Nasser on 25/06/2020.

#include <NasNas/core/graphics/BitmapText.hpp>

#include <NasNas/core/graphics/BitmapFont.hpp>


using namespace ns;

BitmapText::BitmapText() :
m_vertices(sf::PrimitiveType::Triangles),
m_need_update(true)
{}

BitmapText::BitmapText(const sf::String& string, const ns::BitmapFont& font) :
m_string(string),
m_font(&font),
m_vertices(sf::PrimitiveType::Triangles),
m_need_update(true)
{}

void BitmapText::setString(const sf::String& string) {
    m_string = string;
    m_need_update = true;
}

auto BitmapText::getString() -> const sf::String& {
    return m_string;
}

auto BitmapText::getFont() const -> const BitmapFont* {
    return m_font;
}

void BitmapText::setFont(const BitmapFont& font) {
    m_font = &font;
    m_need_update = true;
}

void BitmapText::setColor(const sf::Color &color) {
    m_color = color;
    m_need_update = true;
}

auto BitmapText::getColor() const -> const sf::Color& {
    return m_color;
}

void BitmapText::setLetterSpacing(float factor) {
    m_letter_spacing = factor;
    m_need_update = true;
}

auto BitmapText::getLetterSpacing() const -> float {
    return m_letter_spacing;
}

void BitmapText::setLineSpacing(float factor) {
    m_line_spacing = factor;
    m_need_update = true;
}

auto BitmapText::getLineSpacing() const -> float {
    return m_line_spacing;
}

auto BitmapText::getPosition() const -> sf::Vector2f {
    return sf::Transformable::getPosition();
}

auto BitmapText::getLocalBounds() const -> ns::FloatRect {
    if (m_need_update)
        updateVertices();
    return {{0, 0}, m_size};
}

auto BitmapText::getGlobalBounds() const -> ns::FloatRect {
    return getTransform().transformRect(getLocalBounds());
}

/*
void BitmapText::processString() {
    m_processed_string = m_string;
    if (m_max_width > 0 && m_font != nullptr) {
        // splitting string into words
        std::vector<std::wstring> words;
        auto* str = m_string.data();
        std::wstring current_word;
        while(*str != '\0') {
            if (*str == ' ' || *str == '\n') {
                if (!current_word.empty())
                    words.push_back(current_word);
                words.emplace_back(1, *str);
                current_word = L"";
            }
            else
                current_word += *str;
            str++;
        }
        words.push_back(current_word);

        // inserting new line character when the width exceeds the max width
        int current_width = 0;
        for (auto& w : words) {
            const auto& word_width = getFont()->computeStringSize(w).x;
            if (w == L"\n")
                current_width = 0;
            else if (current_width + word_width > m_max_width) {
                current_width = 0;
                if (w[0] != '\n') {
                    if (w != L" ")
                        w = std::wstring(L"\n").append(w);
                    else
                        w = L"\n";
                }
            }
            current_width += word_width;
        }

        // joining the words into the final processed string
        m_processed_string.clear();
        for (unsigned i = 0; i < words.size(); ++i) {
            auto& word = words[i];
            if (word == L" ")
                if ((i+1 < words.size() && words[i+1][0] == '\n') || i+1 == words.size())
                    continue;
            m_processed_string += words[i];
        }
    }
}
*/

void BitmapText::updateVertices() const {
    m_need_update = false;
    m_vertices.clear();
    if (m_font != nullptr) {
        float x = 0, y = 0;
        float w = 0, h = (float)m_font->getGlyphSize().y;
        float max_w = 0;
        for(const auto& character : m_string) {
            if (character == '\n') {
                max_w = std::max(max_w, w);
                x = 0; y += (float)m_font->getGlyphSize().y * m_line_spacing;
                w = 0; h += (float)m_font->getGlyphSize().y * m_line_spacing;
                continue;
            }
            const auto& glyph = m_font->getGlyph(character);
            // no need to draw vertices for space
            if (character != ' ') {
                auto glyph_size = sf::Vector2f(m_font->getGlyphSize());
                auto glyph_rect = ns::FloatRect(x, y, glyph_size.x, glyph_size.y);
                auto tex_rect = ns::FloatRect(glyph.texture_rect);
                m_vertices.append({glyph_rect.topleft(), m_color, tex_rect.topleft()});
                m_vertices.append({glyph_rect.topright(), m_color, tex_rect.topright()});
                m_vertices.append({glyph_rect.bottomleft(), m_color, tex_rect.bottomleft()});
                m_vertices.append({glyph_rect.bottomleft(), m_color, tex_rect.bottomleft()});
                m_vertices.append({glyph_rect.topright(), m_color, tex_rect.topright()});
                m_vertices.append({glyph_rect.bottomright(), m_color, tex_rect.bottomright()});
            }
            x += (float)glyph.advance * m_letter_spacing;
            w += (float)glyph.advance * m_letter_spacing;
        }
        m_size.x = std::max(max_w, w);
        m_size.y = h;
    }
}

void BitmapText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (m_font != nullptr) {
        states.texture = m_font->getTexture();
        states.transform *= getTransform();
        target.draw(m_vertices, states);
    }
}
