// Created by Modar Nasser on 23/10/2021.

#include <NasNas/ui/NineSlice.hpp>

#include <array>

using namespace ns;
using namespace ns::ui;

NineSlice::NineSlice(Mode mode) : m_mode(mode) {
    m_vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
}

NineSlice::NineSlice(const sf::Texture& texture, NineSlice::Mode mode) :
NineSlice(mode) {
    setTexture(texture);
}

NineSlice::NineSlice(const sf::Texture& texture, const sf::IntRect& rect, NineSlice::Mode mode) :
NineSlice(texture, mode) {
    setTextureRect(rect);
}

void NineSlice::setMode(Mode mode) {
    m_mode = mode;
}

void NineSlice::setTexture(const sf::Texture& texture, bool reset_rect) {
    m_texture = &texture;
    auto size = texture.getSize();
    if (m_texture_rect == ns::FloatRect(0, 0, 0, 0) || reset_rect)
        m_texture_rect = ns::FloatRect(0, 0, size.x, size.y);
}

void NineSlice::setTextureRect(const sf::IntRect& rect) {
    m_texture_rect = rect;
}

void NineSlice::setSlices(int left, int right, int top, int bottom) {
    auto sidewidth = m_texture_rect.width - right - left;
    auto sideheight = m_texture_rect.height - bottom - top;

    m_texture_slices.center = ns::FloatRect(left, top, sidewidth, sideheight);
    m_texture_slices.left = ns::FloatRect(0, top, left, sideheight);
    m_texture_slices.right = ns::FloatRect(left + sidewidth, top, right, sideheight);
    m_texture_slices.top = ns::FloatRect(left, 0, sidewidth, top);
    m_texture_slices.bot = ns::FloatRect(left, top + sideheight, sidewidth, bottom);
    m_texture_slices.topleft = ns::FloatRect(0, 0, left, top);
    m_texture_slices.topright = ns::FloatRect(left + sidewidth, 0, right, top);
    m_texture_slices.botleft = ns::FloatRect(0, top + sideheight, left, bottom);
    m_texture_slices.botright = ns::FloatRect(left + sidewidth, top + sideheight, right, bottom);

    if (m_size != sf::Vector2f(0.f, 0.f)) {
        updateVertices();
    }
}

void NineSlice::setSize(const sf::Vector2i& size) {
    setSize(size.x, size.y);
}

void NineSlice::setSize(int width, int height) {
    m_size.x = width;
    m_size.y = height;
    updateVertices();
}

auto NineSlice::getSize() -> const sf::Vector2f& {
    return m_size;
}

auto NineSlice::getGlobalBounds() const -> sf::FloatRect {
    return getTransform().transformRect(m_vertices.getBounds());
}

void NineSlice::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = m_texture;
    target.draw(m_vertices, states);
}

void NineSlice::updateVertices() {
    if (m_texture == nullptr) return;

    std::array<sf::Vector2f, 9> offsets = {{
        m_texture_slices.topleft.size(),
        {0.f, m_texture_slices.topleft.height},
        {m_texture_slices.topleft.width + m_size.x, m_texture_slices.topleft.height},
        {m_texture_slices.topleft.width, 0.f},
        {m_texture_slices.topleft.width, m_texture_slices.topleft.height + m_size.y},
        {0.f, 0.f},
        {m_texture_slices.topleft.width + m_size.x, 0.f},
        {0.f, m_texture_slices.topleft.height + m_size.y},
        m_texture_slices.topleft.size() + m_size
    }};
    std::array<sf::Vector2f, 9> sizes = {{
        m_size,
        sf::Vector2f(m_texture_slices.left.width, m_size.y),
        sf::Vector2f(m_texture_slices.right.width, m_size.y),
        sf::Vector2f(m_size.x, m_texture_slices.top.height),
        sf::Vector2f(m_size.x, m_texture_slices.bot.height),
        m_texture_slices.topleft.size(),
        m_texture_slices.topright.size(),
        m_texture_slices.botleft.size(),
        m_texture_slices.botright.size()
    }};
    std::array<ns::FloatRect, 9> slices = {{
        m_texture_slices.center,
        m_texture_slices.left,
        m_texture_slices.right,
        m_texture_slices.top,
        m_texture_slices.bot,
        m_texture_slices.topleft,
        m_texture_slices.topright,
        m_texture_slices.botleft,
        m_texture_slices.botright
    }};

    auto x_tiles = static_cast<int>(m_size.x / m_texture_slices.center.width + 1);
    auto y_tiles = static_cast<int>(m_size.y / m_texture_slices.center.height + 1);
    int vertex_count = 4*6;
    if (m_mode == Mode::Repeat) {
        vertex_count += 2*x_tiles*6 + 2*y_tiles*6 + x_tiles*y_tiles*6;
    } else {
        vertex_count += 5*6;
    }
    m_vertices.clear();
    m_vertices.resize(vertex_count);

    if (m_mode == Mode::Repeat) {
        int i = 0;
        {
            auto& slice = slices[Slices::CENTER];
            auto& base_offset = offsets[Slices::CENTER];
            for (int x = 0; x < x_tiles; ++x) {
                for (int y = 0; y < y_tiles; ++y) {
                    auto offset = base_offset;
                    offset.x += (i % x_tiles) * slice.width;
                    offset.y += (i / x_tiles) * slice.height;

                    m_vertices[i*6 + 0].position = offset;
                    m_vertices[i*6 + 1].position = offset + sf::Vector2f(slice.width, 0.f);
                    m_vertices[i*6 + 2].position = offset + slice.size();
                    m_vertices[i*6 + 3].position = offset;
                    m_vertices[i*6 + 4].position = offset + slice.size();
                    m_vertices[i*6 + 5].position = offset + sf::Vector2f(0, slice.height);

                    m_vertices[i*6 + 0].texCoords = m_texture_rect.topleft() + slice.topleft();
                    m_vertices[i*6 + 1].texCoords = m_texture_rect.topleft() + slice.topright();
                    m_vertices[i*6 + 2].texCoords = m_texture_rect.topleft() + slice.bottomright();
                    m_vertices[i*6 + 3].texCoords = m_texture_rect.topleft() + slice.topleft();
                    m_vertices[i*6 + 4].texCoords = m_texture_rect.topleft() + slice.bottomright();
                    m_vertices[i*6 + 5].texCoords = m_texture_rect.topleft() + slice.bottomleft();

                    i+=1;
                }
            }
        }
        {
            auto& slice_top = slices[Slices::TOP];
            auto& slice_bot = slices[Slices::BOT];
            auto& offset_top = offsets[Slices::TOP];
            auto& offset_bot = offsets[Slices::BOT];
            for (int x = 0; x < x_tiles; ++x) {
                m_vertices[i*6 + 0].position = offset_top + sf::Vector2f(x*slice_top.width, 0.f);
                m_vertices[i*6 + 1].position = offset_top + sf::Vector2f(x*slice_top.width, 0.f) + sf::Vector2f(slice_top.width, 0.f);
                m_vertices[i*6 + 2].position = offset_top + sf::Vector2f(x*slice_top.width, 0.f) + slice_top.size();
                m_vertices[i*6 + 3].position = offset_top + sf::Vector2f(x*slice_top.width, 0.f);
                m_vertices[i*6 + 4].position = offset_top + sf::Vector2f(x*slice_top.width, 0.f) + slice_top.size();
                m_vertices[i*6 + 5].position = offset_top + sf::Vector2f(x*slice_top.width, 0.f) + sf::Vector2f(0.f, slice_top.height);

                m_vertices[i*6 + 0].texCoords = m_texture_rect.topleft() + slice_top.topleft();
                m_vertices[i*6 + 1].texCoords = m_texture_rect.topleft() + slice_top.topright();
                m_vertices[i*6 + 2].texCoords = m_texture_rect.topleft() + slice_top.bottomright();
                m_vertices[i*6 + 3].texCoords = m_texture_rect.topleft() + slice_top.topleft();
                m_vertices[i*6 + 4].texCoords = m_texture_rect.topleft() + slice_top.bottomright();
                m_vertices[i*6 + 5].texCoords = m_texture_rect.topleft() + slice_top.bottomleft();

                m_vertices[(i+1)*6 + 0].position = offset_bot + sf::Vector2f(x*slice_bot.width, 0.f);
                m_vertices[(i+1)*6 + 1].position = offset_bot + sf::Vector2f(x*slice_bot.width, 0.f) + sf::Vector2f(slice_bot.width, 0.f);
                m_vertices[(i+1)*6 + 2].position = offset_bot + sf::Vector2f(x*slice_bot.width, 0.f) + slice_bot.size();
                m_vertices[(i+1)*6 + 3].position = offset_bot + sf::Vector2f(x*slice_bot.width, 0.f);
                m_vertices[(i+1)*6 + 4].position = offset_bot + sf::Vector2f(x*slice_bot.width, 0.f) + slice_bot.size();
                m_vertices[(i+1)*6 + 5].position = offset_bot + sf::Vector2f(x*slice_bot.width, 0.f) + sf::Vector2f(0.f, slice_bot.height);

                m_vertices[(i+1)*6 + 0].texCoords = m_texture_rect.topleft() + slice_bot.topleft();
                m_vertices[(i+1)*6 + 1].texCoords = m_texture_rect.topleft() + slice_bot.topright();
                m_vertices[(i+1)*6 + 2].texCoords = m_texture_rect.topleft() + slice_bot.bottomright();
                m_vertices[(i+1)*6 + 3].texCoords = m_texture_rect.topleft() + slice_bot.topleft();
                m_vertices[(i+1)*6 + 4].texCoords = m_texture_rect.topleft() + slice_bot.bottomright();
                m_vertices[(i+1)*6 + 5].texCoords = m_texture_rect.topleft() + slice_bot.bottomleft();

                i+=2;
            }
        }

        {
            auto& slice_left = slices[Slices::LEFT];
            auto& slice_right = slices[Slices::RIGHT];
            auto& offset_left = offsets[Slices::LEFT];
            auto& offset_right = offsets[Slices::RIGHT];
            for (int y = 0; y < y_tiles; ++y) {
                m_vertices[i*6 + 0].position = offset_left + sf::Vector2f(0.f, y*slice_left.height);
                m_vertices[i*6 + 1].position = offset_left + sf::Vector2f(0.f, y*slice_left.height) + sf::Vector2f(slice_left.width, 0.f);
                m_vertices[i*6 + 2].position = offset_left + sf::Vector2f(0.f, y*slice_left.height) + slice_left.size();
                m_vertices[i*6 + 3].position = offset_left + sf::Vector2f(0.f, y*slice_left.height);
                m_vertices[i*6 + 4].position = offset_left + sf::Vector2f(0.f, y*slice_left.height) + slice_left.size();
                m_vertices[i*6 + 5].position = offset_left + sf::Vector2f(0.f, y*slice_left.height) + sf::Vector2f(0.f, slice_left.height);

                m_vertices[i*6 + 0].texCoords = m_texture_rect.topleft() + slice_left.topleft();
                m_vertices[i*6 + 1].texCoords = m_texture_rect.topleft() + slice_left.topright();
                m_vertices[i*6 + 2].texCoords = m_texture_rect.topleft() + slice_left.bottomright();
                m_vertices[i*6 + 3].texCoords = m_texture_rect.topleft() + slice_left.topleft();
                m_vertices[i*6 + 4].texCoords = m_texture_rect.topleft() + slice_left.bottomright();
                m_vertices[i*6 + 5].texCoords = m_texture_rect.topleft() + slice_left.bottomleft();

                m_vertices[(i+1)*6 + 0].position = offset_right + sf::Vector2f(0.f, y*slice_right.height);
                m_vertices[(i+1)*6 + 1].position = offset_right + sf::Vector2f(0.f, y*slice_right.height) + sf::Vector2f(slice_right.width, 0.f);
                m_vertices[(i+1)*6 + 2].position = offset_right + sf::Vector2f(0.f, y*slice_right.height) + slice_right.size();
                m_vertices[(i+1)*6 + 3].position = offset_right + sf::Vector2f(0.f, y*slice_right.height);
                m_vertices[(i+1)*6 + 4].position = offset_right + sf::Vector2f(0.f, y*slice_right.height) + slice_right.size();
                m_vertices[(i+1)*6 + 5].position = offset_right + sf::Vector2f(0.f, y*slice_right.height) + sf::Vector2f(0.f, slice_right.height);

                m_vertices[(i+1)*6 + 0].texCoords = m_texture_rect.topleft() + slice_right.topleft();
                m_vertices[(i+1)*6 + 1].texCoords = m_texture_rect.topleft() + slice_right.topright();
                m_vertices[(i+1)*6 + 2].texCoords = m_texture_rect.topleft() + slice_right.bottomright();
                m_vertices[(i+1)*6 + 3].texCoords = m_texture_rect.topleft() + slice_right.topleft();
                m_vertices[(i+1)*6 + 4].texCoords = m_texture_rect.topleft() + slice_right.bottomright();
                m_vertices[(i+1)*6 + 5].texCoords = m_texture_rect.topleft() + slice_right.bottomleft();

                i+=2;
            }
        }
    }

    int first_slice = m_mode == Mode::Repeat ? Slices::TL : Slices::CENTER;
    int first_vertex = m_mode == Mode::Repeat ? vertex_count-4*6 : 0;
    for (int s = first_slice, v = first_vertex; v < vertex_count; ++s, v+=6) {
        auto& offset = offsets[s];
        auto& size = sizes[s];
        auto& slice = slices[s];
        m_vertices[v + 0].position = offset;
        m_vertices[v + 1].position = offset + sf::Vector2f(size.x, 0.f);
        m_vertices[v + 2].position = offset + size;
        m_vertices[v + 3].position = offset;
        m_vertices[v + 4].position = offset + size;
        m_vertices[v + 5].position = offset + sf::Vector2f(0.f, size.y);

        m_vertices[v + 0].texCoords = m_texture_rect.topleft() + slice.topleft();
        m_vertices[v + 1].texCoords = m_texture_rect.topleft() + slice.topright();
        m_vertices[v + 2].texCoords = m_texture_rect.topleft() + slice.bottomright();
        m_vertices[v + 3].texCoords = m_texture_rect.topleft() + slice.topleft();
        m_vertices[v + 4].texCoords = m_texture_rect.topleft() + slice.bottomright();
        m_vertices[v + 5].texCoords = m_texture_rect.topleft() + slice.bottomleft();
    }
}
