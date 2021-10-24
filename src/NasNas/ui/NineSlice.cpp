// Created by Modar Nasser on 23/10/2021.

#include <array>
#include "NasNas/ui/NineSlice.hpp"

using namespace ns;
using namespace ns::ui;

NineSlice::NineSlice(const sf::Texture& texture, NineSlice::Mode mode) :
m_mode(mode) {
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
    setTexture(texture);
}

NineSlice::NineSlice(const sf::Texture& texture, const sf::IntRect& rect, NineSlice::Mode mode) :
NineSlice(texture, mode) {
    setTextureRect(rect);
}

void NineSlice::setTexture(const sf::Texture& texture) {
    m_texture = &texture;
    auto size = texture.getSize();
    m_texture_rect = ns::FloatRect(0, 0, size.x, size.y);
}

void NineSlice::setTextureRect(const sf::IntRect& rect) {
    m_texture_rect = rect;
}

void NineSlice::setSlices(int left, int right, int top, int bottom) {
    auto sidewidth = m_texture_rect.width - right - left;
    auto sideheight = m_texture_rect.height - bottom - top;

    m_texture_slices.topleft = ns::FloatRect(0, 0, left, top);
    m_texture_slices.topright = ns::FloatRect(left + sidewidth, 0, right, top);
    m_texture_slices.botleft = ns::FloatRect(0, top + sideheight, left, bottom);
    m_texture_slices.botright = ns::FloatRect(left + sidewidth, top + sideheight, right, bottom);
    m_texture_slices.center = ns::FloatRect(left, top, sidewidth, sideheight);
    m_texture_slices.left = ns::FloatRect(0, top, left, sideheight);
    m_texture_slices.right = ns::FloatRect(left + sidewidth, top, right, sideheight);
    m_texture_slices.top = ns::FloatRect(left, 0, sidewidth, top);
    m_texture_slices.bot = ns::FloatRect(left, top + sideheight, sidewidth, bottom);
}

void NineSlice::setSize(const sf::Vector2i& size) {
    setSize(size.x, size.y);
}

void NineSlice::setSize(int width, int height) {
    m_size.x = width;
    m_size.y = height;
    updateVertices();
}

auto NineSlice::getGlobalBounds() const -> sf::FloatRect {
    return getTransform().transformRect(m_vertices.getBounds());
}

void NineSlice::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = m_texture;
    target.draw(m_vertices, states);
}

#include "NasNas/core/data/Logger.hpp"

void NineSlice::updateVertices() {
    if (m_texture == nullptr) return;

    m_vertices.resize(9*6);

    std::array<sf::Vector2f, 9> offsets = {{
            {0.f, 0.f},
            {m_texture_slices.topleft.width + m_size.x, 0.f},
            {0.f, m_texture_slices.topleft.height + m_size.y},
            m_texture_slices.topleft.size() + m_size,
            m_texture_slices.topleft.size(),
            {0.f, m_texture_slices.topleft.height},
            {m_texture_slices.topleft.width + m_size.x, m_texture_slices.topleft.height},
            {m_texture_slices.topleft.width, 0.f},
            {m_texture_slices.topleft.width, m_texture_slices.topleft.height + m_size.y}
    }};
    std::array<sf::Vector2f, 9> sizes = {{
        m_texture_slices.topleft.size(),
        m_texture_slices.topright.size(),
        m_texture_slices.botleft.size(),
        m_texture_slices.botright.size(),
        m_size,
        sf::Vector2f(m_texture_slices.left.width, m_size.y),
        sf::Vector2f(m_texture_slices.right.width, m_size.y),
        sf::Vector2f(m_size.x, m_texture_slices.top.height),
        sf::Vector2f(m_size.x, m_texture_slices.bot.height),
    }};
    std::array<ns::FloatRect, 9> slices = {{
        m_texture_slices.topleft,
        m_texture_slices.topright,
        m_texture_slices.botleft,
        m_texture_slices.botright,
        m_texture_slices.center,
        m_texture_slices.left,
        m_texture_slices.right,
        m_texture_slices.top,
        m_texture_slices.bot
    }};

    for (int i = 0; i < 9; ++i) {
        auto& offset = offsets[i];
        auto& size = sizes[i];
        auto& slice = slices[i];
        m_vertices[i*6 + 0].position = offset;
        m_vertices[i*6 + 1].position = offset + sf::Vector2f(size.x, 0.f);
        m_vertices[i*6 + 2].position = offset + size;
        m_vertices[i*6 + 3].position = offset;
        m_vertices[i*6 + 4].position = offset + size;
        m_vertices[i*6 + 5].position = offset + sf::Vector2f(0, size.y);

        m_vertices[i*6 + 0].texCoords = m_texture_rect.topleft() + slice.topleft();
        m_vertices[i*6 + 1].texCoords = m_texture_rect.topleft() + slice.topright();
        m_vertices[i*6 + 2].texCoords = m_texture_rect.topleft() + slice.bottomright();
        m_vertices[i*6 + 3].texCoords = m_texture_rect.topleft() + slice.topleft();
        m_vertices[i*6 + 4].texCoords = m_texture_rect.topleft() + slice.bottomright();
        m_vertices[i*6 + 5].texCoords = m_texture_rect.topleft() + slice.bottomleft();
    }
}
