// Created by Modar Nasser on 20/04/2021.

#include "NasNas/core/graphics/Sprite.hpp"

using namespace ns;

Sprite::Sprite(const sf::Texture& texture) {
    setTexture(texture, true);
}

Sprite::Sprite(const sf::Texture& texture, const sf::IntRect& rectangle) {
    setTextureRect(rectangle);
    setTexture(texture);
}

Sprite::Sprite(const sf::Sprite& other) {
    setTexture(*other.getTexture());
    setTextureRect(other.getTextureRect());
}

void Sprite::setTexture(const sf::Texture& texture, bool reset_rect) {
    if (reset_rect || (m_texture == nullptr && (m_texture_rect == sf::IntRect()))) {
        auto size = sf::Vector2i(texture.getSize());
        setTextureRect({0, 0, size.x, size.y});
    }
    m_texture = & texture;
}

void Sprite::setTextureRect(const sf::IntRect& rectangle) {
    if (rectangle != m_texture_rect) {
        m_texture_rect = rectangle;

        auto bounds = getLocalBounds();
        m_vertices[0].position = bounds.topleft();
        m_vertices[1].position = bounds.topright();
        m_vertices[2].position = bounds.bottomleft();
        m_vertices[3].position = bounds.bottomright();

        auto left   = static_cast<float>(m_texture_rect.left);
        auto right  = left + static_cast<float>(m_texture_rect.width);
        auto top    = static_cast<float>(m_texture_rect.top);
        auto bottom = top + static_cast<float>(m_texture_rect.height);
        m_vertices[0].texCoords = {left, top};
        m_vertices[1].texCoords = {right, top};
        m_vertices[2].texCoords = {left, bottom};
        m_vertices[3].texCoords = {right, bottom};
    }
}

void Sprite::setColor(const sf::Color& color) {
    for (int i = 0; i < 4; ++i)
        setColor(color, i);
}

void Sprite::setColor(const sf::Color& color, unsigned int vert_index) {
    switch (vert_index) {
        case 2: m_vertices[3].color = color; break;
        case 3: m_vertices[2].color = color; break;
        default: m_vertices[vert_index].color = color;
    }
}

auto Sprite::getTexture() const -> const sf::Texture* {
    return m_texture;
}

auto Sprite::getTextureRect() const -> const IntRect& {
    return m_texture_rect;
}

auto Sprite::getColor() const -> const sf::Color& {
    return m_vertices[0].color;
}

auto Sprite::getColor(unsigned int vert_index) const -> const sf::Color& {
    switch (vert_index) {
        case 2: return m_vertices[3].color;
        case 3: return m_vertices[2].color;
        default: return m_vertices[vert_index].color;
    }
}

auto Sprite::getVertex(unsigned int index) const -> const sf::Vertex& {
    switch (index) {
        case 2: return m_vertices[3];
        case 3: return m_vertices[2];
        default: return m_vertices[index];
    }
}

auto Sprite::getLocalBounds() const -> ns::FloatRect {
    auto w = static_cast<float>(std::abs(m_texture_rect.width));
    auto h = static_cast<float>(std::abs(m_texture_rect.height));
    return {0, 0, w, h};
}

auto Sprite::getGlobalBounds() const -> ns::FloatRect {
    return getTransform().transformRect(getLocalBounds());
}

void Sprite::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (m_texture) {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, 4, sf::TriangleStrip, states);
    }
}