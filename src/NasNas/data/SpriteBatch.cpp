/**
* Created by Modar Nasser on 06/10/2020.
**/

#include "NasNas/data/SpriteBatch.hpp"

using namespace ns;


std::vector<SpriteBatch*> SpriteBatch::list;

SpriteBatch::SpriteBatch(std::string name) :
m_name(std::move(name)) {
    SpriteBatch::list.push_back(this);
}

SpriteBatch::~SpriteBatch() {
    SpriteBatch::list.erase(std::find(SpriteBatch::list.begin(), SpriteBatch::list.end(), this));
    for (auto& spr : m_owned_sprites)
        delete(spr);
}

void SpriteBatch::draw(sf::Sprite* sprite) {
    m_sprites.push_back(sprite);
    if (m_vertices.count(sprite->getTexture()) == 0)
        m_vertices.insert({sprite->getTexture(), {}});
}

void SpriteBatch::draw(sf::Texture* texture, sf::Vector2f pos, sf::IntRect rect) {
    auto* spr = new sf::Sprite(*texture);
    spr->setTextureRect(rect);
    spr->setPosition(pos);
    m_owned_sprites.push_back(spr);
    draw(spr);
}

void SpriteBatch::end() {
    for (auto& [texture, vector] : m_vertices)
        vector.reserve(m_sprites.size()*6);
}

void SpriteBatch::clear() {
    m_sprites.clear();
    m_vertices.clear();
}

auto SpriteBatch::getPosition() -> sf::Vector2f {
    return m_global_bounds.topleft();
}

auto SpriteBatch::getGlobalBounds() -> ns::FloatRect {
    return m_global_bounds;
}

void SpriteBatch::render() {
    for (auto& [texture, vector] : m_vertices)
        vector.clear();

    for (int i = 0; i < m_sprites.size(); ++i) {
        auto& spr = m_sprites[i];
        const ns::FloatRect& tex_rect{spr->getTextureRect()};
        const ns::FloatRect& lb{spr->getLocalBounds()};
        const ns::FloatRect& rect{spr->getTransform().transformRect(lb)};
        const auto& topleft = spr->getTransform().transformPoint(lb.topleft());
        const auto& topright = spr->getTransform().transformPoint(lb.topright());
        const auto& bottomright = spr->getTransform().transformPoint(lb.bottomright());
        const auto& bottomleft = spr->getTransform().transformPoint(lb.bottomleft());
        m_vertices[spr->getTexture()].emplace_back(topleft, spr->getColor(), tex_rect.topleft());
        m_vertices[spr->getTexture()].emplace_back(bottomright, spr->getColor(), tex_rect.bottomright());
        m_vertices[spr->getTexture()].emplace_back(bottomleft, spr->getColor(), tex_rect.bottomleft());
        m_vertices[spr->getTexture()].emplace_back(topleft, spr->getColor(), tex_rect.topleft());
        m_vertices[spr->getTexture()].emplace_back(topright, spr->getColor(), tex_rect.topright());
        m_vertices[spr->getTexture()].emplace_back(bottomright, spr->getColor(), tex_rect.bottomright());
        if (i == 0)
            m_global_bounds = rect;
        else {
            m_global_bounds.left = std::min(rect.left, m_global_bounds.left);
            m_global_bounds.top = std::min(rect.top, m_global_bounds.top);
            auto right = std::max(rect.right(), m_global_bounds.right());
            auto bottom = std::max(rect.bottom(), m_global_bounds.bottom());
            m_global_bounds.width = right-m_global_bounds.left;
            m_global_bounds.height = bottom-m_global_bounds.top;
        }
    }
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& [texture, vector] : m_vertices) {
        states.texture = texture;
        target.draw(vector.data(), vector.size(), sf::PrimitiveType::Triangles, states);
    }
}
