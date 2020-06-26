/**
* Created by Modar Nasser on 25/06/2020.
**/

#include "NasNas/core/BitmapText.hpp"

using namespace ns;

BitmapGlyph::BitmapGlyph(const IntRect& texture_rect, char character, int spacing) :
        texture_rect(texture_rect),
        character(character),
        advance(spacing)
{}

BitmapFont::BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size) :
BitmapFont(texture, glyph_size, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", {})
{}

BitmapFont::BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size, const std::string& chars_map)  :
BitmapFont(texture, glyph_size, chars_map, {})
{}

BitmapFont::BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size, const std::unordered_map<char, int>& spacings_map) :
BitmapFont(texture, glyph_size, " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~", spacings_map)
{}

BitmapFont::BitmapFont(const sf::Texture& texture, const sf::Vector2i& glyph_size, const std::string& chars_map, const std::unordered_map<char, int>& spacings_map) :
m_texture(&texture) {
    m_glyph_size = glyph_size;
    m_chars_map = chars_map;
    m_advance_map = spacings_map;

    int i = 0;
    for (int y = 0; y < m_texture->getSize().y; y += m_glyph_size.y) {
        for (int x = 0; x < m_texture->getSize().x; x += m_glyph_size.x) {
            if (i < m_chars_map.size()) {
                char character = m_chars_map[i];
                int spacing = m_glyph_size.x;
                if (m_advance_map.count(character) > 0)
                    spacing = m_advance_map[character];
                m_glyphs[character] = new BitmapGlyph({{x, y}, m_glyph_size}, character, spacing);
            }
            i += 1;
        }
    }
}

BitmapFont::~BitmapFont() {
    for (const auto& item : m_glyphs) {
        delete(item.second);
    }
}

auto BitmapFont::getGlyphSize() -> const sf::Vector2i & {
    return m_glyph_size;
}

auto BitmapFont::getTexture() -> const sf::Texture * {
    return m_texture;
}

auto BitmapFont::getGlyph(char character) -> const BitmapGlyph& {
    if (m_glyphs.count(character) > 0) {
        return *m_glyphs[character];
    }
    std::cout << "Selected BitmapFont does not have glyph for character «" << character << "» " << std::endl;
    exit(-1);
}

BitmapText::BitmapText(const std::string& text) {
    m_text = text;
    m_sprite.setPrimitiveType(sf::PrimitiveType::Quads);
}

BitmapText::BitmapText(const std::string& text, const std::shared_ptr<BitmapFont>& font) :
BitmapText(text) {
    setFont(font);
}

void BitmapText::setFont(const std::shared_ptr<BitmapFont>& font) {
    m_font = font;
    float x = 0;
    for(const auto& character : m_text) {
        auto glyph = m_font->getGlyph(character);
        auto glyph_size = (sf::Vector2f)m_font->getGlyphSize();
        auto vertex_tl = sf::Vertex({x, 0}, (sf::Vector2f)glyph.texture_rect.topleft);
        auto vertex_tr = sf::Vertex({x + glyph_size.x, 0}, (sf::Vector2f)glyph.texture_rect.topright);
        auto vertex_br = sf::Vertex({x + glyph_size.x, glyph_size.y}, (sf::Vector2f)glyph.texture_rect.bottomright);
        auto vertex_bl = sf::Vertex({x, glyph_size.y}, (sf::Vector2f)glyph.texture_rect.bottomleft);
        m_sprite.append(vertex_tl);
        m_sprite.append(vertex_tr);
        m_sprite.append(vertex_br);
        m_sprite.append(vertex_bl);
        x += (float)glyph.advance;
    }
}

auto BitmapText::getPosition() -> sf::Vector2f {
    return m_transformable.getPosition();
}

void BitmapText::setPosition(const sf::Vector2f& position) {
    m_transformable.setPosition(position);
}

auto BitmapText::getWidth() -> int {
    int width = 0;
    for (const auto& character : m_text)
        width += m_font->getGlyph(character).advance;
    return width;
}

auto BitmapText::getHeight() -> int {
    return m_font->getGlyphSize().y;
}

auto BitmapText::getSize() -> sf::Vector2f {
    return sf::Vector2f(getWidth(), getHeight());
}

void BitmapText::move(float offsetx, float offsety) {
    m_transformable.move(offsetx, offsety);
}

void BitmapText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (m_font != nullptr) {
        states.texture = m_font->getTexture();
        states.transform *= m_transformable.getTransform();
        target.draw(m_sprite, states);
    }
}
