/**
* Created by Modar Nasser on 25/06/2020.
**/


#include <NasNas/core/graphics/BitmapText.hpp>

#include <iostream>

using namespace ns;


void BitmapFont::loadFromTexture(const sf::Texture& texture, const sf::Vector2u& glyph_size, unsigned advance) {
    m_texture = &texture;
    m_glyph_size = glyph_size;
    m_default_advance = advance;
    setCharacters(default_characters);
}

/*
BitmapFont::BitmapFont(const sf::Texture& texture, const sf::Vector2u& glyph_size, const std::wstring& chars_map, const std::unordered_map<std::wstring, int>& spacings_map, int default_advance) :
m_texture(&texture),
m_glyph_size(glyph_size) {
    m_chars_map = chars_map;
    if (default_advance <= 0)
        default_advance = glyph_size.x;

    unsigned int i = 0;
    for (int y = 0; y < (int)m_texture->getSize().y; y += m_glyph_size.y) {
        for (int x = 0; x < (int)m_texture->getSize().x; x += m_glyph_size.x) {
            if (i < m_chars_map.size()) {
                char character = m_chars_map[i];
                int spacing = default_advance;
                // if (m_advance_map.count(character) > 0)
                //     spacing = m_advance_map[character];
                if (m_glyphs.count(character) == 0)
                    m_glyphs[character].reset(new BitmapGlyph({{x, y}, {(int)m_glyph_size.x, (int)m_glyph_size.y}}, character, spacing));
            }
            i += 1;
        }
    }
}
*/

auto BitmapFont::getTexture() -> const sf::Texture* {
    return m_texture;
}

auto BitmapFont::getGlyphSize() -> const sf::Vector2u& {
    return m_glyph_size;
}

void BitmapFont::setCharacters(const std::wstring& characters) {
    if (m_texture == nullptr)
        return;

    m_glyphs.clear();
    m_glyphs[0] = {{0, 0, 0, 0}, static_cast<wchar_t>(0), 0};

    auto columns = m_texture->getSize().x / m_glyph_size.x;
    for (unsigned i = 0; i < characters.size(); ++i) {
        auto character = characters.at(i);
        auto tex_coords = sf::Vector2i((i % columns)*m_glyph_size.x, (i / columns)*m_glyph_size.y);
        auto tex_rect = ns::IntRect(tex_coords.x, tex_coords.y, m_glyph_size.x, m_glyph_size.y);
        m_glyphs[character] = {tex_rect, character, m_default_advance};
    }
}

void BitmapFont::setCharactersAdvance(const std::map<std::wstring, unsigned int>& advances) {
    for (const auto& [string, advance]: advances) {
        for (const auto& character: string) {
            if (m_glyphs.find(character) != m_glyphs.end()) {
                m_glyphs.at(character).advance = advance;
            }
        }
    }
}

auto BitmapFont::getGlyph(wchar_t character) -> const BitmapGlyph& {
    if (m_glyphs.find(character) != m_glyphs.end()) {
        return m_glyphs.at(character);
    }
    return m_glyphs.at(0);
}

auto BitmapFont::computeStringSize(const std::wstring& string) -> sf::Vector2i {
    int h = getGlyphSize().y;
    int w = 0, max_width = 0;
    for (const auto character : string) {
        if (character == '\n') {
            h += getGlyphSize().y;
            max_width = std::max(w, max_width);
            w = 0;
            continue;
        }
        w += getGlyph(character).advance;
    }
    max_width = std::max(w, max_width);
    return {max_width, h};
}


BitmapText::BitmapText(const std::wstring& text, ns::BitmapFont* font) {
    setFont(font);
    m_vertices.setPrimitiveType(sf::PrimitiveType::Quads);
    setString(text);
}

auto BitmapText::getString() -> const std::wstring& {
    return m_string;
}

void BitmapText::setString(const std::wstring &string) {
    m_string = string;
    processString();
    updateVertices();
}

auto BitmapText::getFont() -> BitmapFont* {
    return m_font;
}

void BitmapText::setFont(const std::shared_ptr<BitmapFont>& font) {
    setFont(font.get());
}
void BitmapText::setFont(BitmapFont* font) {
    if (font != nullptr) {
        m_font = font;
        processString();
        updateVertices();
    }
}

void BitmapText::setColor(const sf::Color &color) {
    m_color = color;
    updateVertices();
}

auto BitmapText::getPosition() const -> sf::Vector2f {
    return sf::Transformable::getPosition();
}

auto BitmapText::getGlobalBounds() const -> ns::FloatRect {
    return getTransform().transformRect({{0, 0}, getSize()});
}

void BitmapText::setMaxWidth(int max_width) {
    m_max_width = max_width;
    processString();
    updateVertices();
}

auto BitmapText::getSize() const -> sf::Vector2f {
    return {static_cast<float>(m_width), static_cast<float>(m_height)};
}

auto BitmapText::getProcessedString() -> const std::wstring& {
    return m_processed_string;
}

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

void BitmapText::updateVertices() {
    m_vertices.clear();
    if (m_font != nullptr) {
        float x = 0, y = 0;
        int w = 0, h = m_font->getGlyphSize().y;
        int max_w = 0;
        for(const auto& character : m_processed_string) {
            if (character == '\n') {
                x = 0;
                y += (float)m_font->getGlyphSize().y;
                max_w = std::max(max_w, w);
                w = 0;
                h += m_font->getGlyphSize().y;
                continue;
            }
            auto glyph = m_font->getGlyph(character);
            auto glyph_size = (sf::Vector2f)m_font->getGlyphSize();
            auto vertex_tl = sf::Vertex({x, y}, m_color, sf::Vector2f(glyph.texture_rect.topleft()));
            auto vertex_tr = sf::Vertex({x + glyph_size.x, y}, m_color, sf::Vector2f(glyph.texture_rect.topright()));
            auto vertex_br = sf::Vertex({x + glyph_size.x, y + glyph_size.y}, m_color, sf::Vector2f(glyph.texture_rect.bottomright()));
            auto vertex_bl = sf::Vertex({x, y + glyph_size.y}, m_color, sf::Vector2f(glyph.texture_rect.bottomleft()));
            m_vertices.append(vertex_tl);
            m_vertices.append(vertex_tr);
            m_vertices.append(vertex_br);
            m_vertices.append(vertex_bl);
            x += (float)glyph.advance;
            w += glyph.advance;
        }
        m_width = std::max(max_w, w);
        m_height = h;
    }
}

void BitmapText::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (m_font != nullptr) {
        states.texture = m_font->getTexture();
        states.transform *= getTransform();
        target.draw(m_vertices, states);
    }
}
