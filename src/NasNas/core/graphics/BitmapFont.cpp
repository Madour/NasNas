// Created by Modar Nasser on 17/02/2022.

#include <NasNas/core/graphics/BitmapFont.hpp>


using namespace ns;

void BitmapFont::loadFromTexture(const sf::Texture& texture, const sf::Vector2u& glyph_size, unsigned advance) {
    m_texture = &texture;
    m_glyph_size = glyph_size;
    m_default_advance = advance;
    setCharacters(default_characters);
}

auto BitmapFont::getTexture() const -> const sf::Texture* {
    return m_texture;
}

auto BitmapFont::getGlyphSize() const -> const sf::Vector2u& {
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

    if (characters.find(' ') == std::wstring::npos) {
        m_glyphs[' '] = {{0, 0, 0, 0}, ' ', m_default_advance};
    }
}

void BitmapFont::setCharactersAdvance(const std::map<std::wstring, unsigned int>& advances) {
    for (const auto& [string, advance]: advances) {
        for (const auto& character: string) {
            if (m_glyphs.find(character) != m_glyphs.end()) {
                m_glyphs.at(character).advance = static_cast<float>(advance);
            }
        }
    }
}

auto BitmapFont::getGlyph(wchar_t character) const -> const BitmapGlyph& {
    if (m_glyphs.find(character) != m_glyphs.end()) {
        return m_glyphs.at(character);
    }
    return m_glyphs.at(0);
}

auto BitmapFont::computeStringSize(const std::wstring& string) const -> sf::Vector2f {
    unsigned h = getGlyphSize().y;
    float w = 0, max_w = 0;
    for (const auto& character : string) {
        if (character == '\n') {
            h += getGlyphSize().y;
            max_w = std::max(w, max_w);
            w = 0;
            continue;
        }
        w += getGlyph(character).advance;
    }
    max_w = std::max(w, max_w);
    return {max_w, static_cast<float>(h)};
}

