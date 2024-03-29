/**
* Created by Modar Nasser on 06/10/2020.
**/

#include <NasNas/core/graphics/SpriteBatch.hpp>

using namespace ns;


SpriteBatch::SpriteBatchLayer::SpriteBatchLayer(const sf::Texture* tex) :
texture(tex)
{}

SpriteBatch::SpriteBatch() : m_usage(sf::VertexBuffer::Usage::Stream) {
    clear();
}

void SpriteBatch::clear() {
    m_gc.clear();
    m_layers.clear();
    m_global_bounds = {0, 0, 0, 0};
}

void SpriteBatch::start(sf::VertexBuffer::Usage usage) {
    m_usage = usage;
}

void SpriteBatch::setDrawOrder(DrawOrder order) {
    m_draw_order = order;
}

void SpriteBatch::draw(const ns::Sprite* sprite) {
    if (m_draw_order == DrawOrder::Front) {
        if (m_layers.empty() || m_layers.back().texture != sprite->getTexture()) {
            m_layers.emplace_back(sprite->getTexture());
        }
        m_layers.back().sprites.push_back(sprite);
    }
    else {
        if (m_layers.empty() || m_layers.front().texture != sprite->getTexture()) {
            m_layers.emplace_front(sprite->getTexture());
        }
        m_layers.front().sprites.emplace(m_layers.front().sprites.begin(), sprite);
    }
    m_need_end = true;
    m_need_render = true;
}

void SpriteBatch::draw(const sf::Texture* texture, const sf::Vector2f& pos, const sf::IntRect& rect, const sf::Color& color) {
    auto* spr = new ns::Sprite(*texture);
    spr->setTextureRect(rect);
    spr->setPosition(pos);
    spr->setColor(color);
    m_gc.emplace_back(spr);
    draw(spr);
}

void SpriteBatch::draw(const sf::Texture* texture, const sf::IntRect& rect, const sf::Transformable& tr, const sf::Color& color) {
    auto* spr = new ns::Sprite(*texture);
    spr->setTextureRect(rect);
    spr->setPosition(tr.getPosition());
    spr->setRotation(tr.getRotation());
    spr->setScale(tr.getScale());
    spr->setColor(color);
    m_gc.emplace_back(spr);
    draw(spr);
}

void SpriteBatch::erase(const ns::Sprite* sprite) {
    for (auto& layer : m_layers) {
        auto& vec = layer.sprites;
        vec.erase(std::remove(vec.begin(), vec.end(), sprite), vec.end());
    }
    m_need_end = true;
    m_need_render = true;
}

void SpriteBatch::end() {
    for (auto& layer : m_layers) {
        layer.vertices.resize(layer.sprites.size()*6);
        layer.buffer.create(layer.sprites.size()*6);
        layer.buffer.setUsage(m_usage);
        layer.buffer.setPrimitiveType(sf::PrimitiveType::Triangles);
    }
    m_need_end = false;
}

auto SpriteBatch::getDepth() const -> unsigned {
    return m_layers.size();
}

auto SpriteBatch::getUsage() const -> sf::VertexBuffer::Usage {
    return m_usage;
}

auto SpriteBatch::getPosition() const -> sf::Vector2f {
    return m_global_bounds.topleft();
}

auto SpriteBatch::getGlobalBounds() const -> ns::FloatRect {
    return m_global_bounds;
}

void SpriteBatch::render() {
    if (m_usage == sf::VertexBuffer::Usage::Static && !m_need_render)
        return;
    m_need_render = false;

    if (m_need_end)
        end();

    bool first = true;
    for (auto& layer : m_layers) {
        for (unsigned int i = 0; i < layer.sprites.size(); ++i) {
            auto* spr = layer.sprites[i];

            const auto& transform = spr->getTransform();
            const ns::FloatRect tex_rect{spr->getTextureRect()};
            const ns::FloatRect lb{spr->getLocalBounds()};
            const ns::FloatRect rect{transform.transformRect(lb)};

            const auto& topleft = transform.transformPoint(lb.topleft());
            const auto& topright = transform.transformPoint(lb.topright());
            const auto& bottomright = transform.transformPoint(lb.bottomright());
            const auto& bottomleft = transform.transformPoint(lb.bottomleft());

            layer.vertices[i*6+0].position = topleft;
            layer.vertices[i*6+1].position = topright;
            layer.vertices[i*6+2].position = bottomright;
            layer.vertices[i*6+3].position = topleft;
            layer.vertices[i*6+4].position = bottomright;
            layer.vertices[i*6+5].position = bottomleft;

            layer.vertices[i*6+0].color = spr->getColor(0);
            layer.vertices[i*6+1].color = spr->getColor(1);
            layer.vertices[i*6+2].color = spr->getColor(2);
            layer.vertices[i*6+3].color = spr->getColor(0);
            layer.vertices[i*6+4].color = spr->getColor(2);
            layer.vertices[i*6+5].color = spr->getColor(3);

            layer.vertices[i*6+0].texCoords = tex_rect.topleft();
            layer.vertices[i*6+1].texCoords = tex_rect.topright();
            layer.vertices[i*6+2].texCoords = tex_rect.bottomright();
            layer.vertices[i*6+3].texCoords = tex_rect.topleft();
            layer.vertices[i*6+4].texCoords = tex_rect.bottomright();
            layer.vertices[i*6+5].texCoords = tex_rect.bottomleft();

            if (first) {
                m_global_bounds = rect;
                first = false;
            }
            else {
                auto left = std::min(rect.left, m_global_bounds.left);
                auto top = std::min(rect.top, m_global_bounds.top);
                auto right = std::max(rect.right(), m_global_bounds.right());
                auto bottom = std::max(rect.bottom(), m_global_bounds.bottom());
                m_global_bounds.left = left;
                m_global_bounds.top = top;
                m_global_bounds.width = right - left;
                m_global_bounds.height = bottom - top;
            }
        }
        layer.buffer.update(layer.vertices.data());
    }
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& layer : m_layers) {
        states.texture = layer.texture;
        target.draw(layer.buffer, states);
    }
}
