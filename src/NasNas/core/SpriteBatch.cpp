/**
* Created by Modar Nasser on 06/10/2020.
**/

#include "NasNas/core/SpriteBatch.hpp"

using namespace ns;


std::vector<SpriteBatch*> SpriteBatch::list;

SpriteBatch::SpriteBatch(std::string name) :
m_name(std::move(name)) {
    SpriteBatch::list.push_back(this);
    clear();
}

SpriteBatch::~SpriteBatch() {
    SpriteBatch::list.erase(std::find(SpriteBatch::list.begin(), SpriteBatch::list.end(), this));
    for (auto& spr : m_owned_sprites)
        delete(spr);
}

void SpriteBatch::draw(sf::Sprite* sprite) {
    if (m_sprites.empty())
        m_sprites.emplace_back();
    if (!m_sprites[m_sprites.size()-1].empty())
            if (m_sprites[m_sprites.size()-1][0]->getTexture() != sprite->getTexture())
                m_sprites.emplace_back();
    m_sprites[m_sprites.size()-1].push_back(sprite);
}

void SpriteBatch::draw(sf::Texture* texture, sf::Vector2f pos, sf::IntRect rect) {
    auto* spr = new sf::Sprite(*texture);
    spr->setTextureRect(rect);
    spr->setPosition(pos);
    m_owned_sprites.push_back(spr);
    draw(spr);
}

void SpriteBatch::end() {
    for (int i = 0; i < m_sprites.size(); ++i) {
        m_vertices.emplace_back();
        m_vertices[i].second.reserve(m_sprites[i].size()*6);
    }
}

void SpriteBatch::clear() {
    m_vertices.clear();
    m_sprites.clear();
    for (auto& spr : m_owned_sprites)
        delete(spr);
    m_global_bounds = {0, 0, 0, 0};
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
    m_vertices.clear();

    for (int order = 0; order < m_sprites.size() ; ++order) {
        auto& sprites = m_sprites[order];
        if (!sprites.empty())
            m_vertices.push_back({sprites[0]->getTexture(), {}});
        for (int i = 0; i < sprites.size(); ++i) {
            auto& spr = sprites[i];
            const ns::FloatRect tex_rect{spr->getTextureRect()};
            const ns::FloatRect lb{spr->getLocalBounds()};
            const ns::FloatRect rect{spr->getTransform().transformRect(lb)};
            const auto& topleft = spr->getTransform().transformPoint(lb.topleft());
            const auto& topright = spr->getTransform().transformPoint(lb.topright());
            const auto& bottomright = spr->getTransform().transformPoint(lb.bottomright());
            const auto& bottomleft = spr->getTransform().transformPoint(lb.bottomleft());
            m_vertices[order].second.emplace_back(topleft, spr->getColor(), tex_rect.topleft());
            m_vertices[order].second.emplace_back(bottomright, spr->getColor(), tex_rect.bottomright());
            m_vertices[order].second.emplace_back(bottomleft, spr->getColor(), tex_rect.bottomleft());
            m_vertices[order].second.emplace_back(topleft, spr->getColor(), tex_rect.topleft());
            m_vertices[order].second.emplace_back(topright, spr->getColor(), tex_rect.topright());
            m_vertices[order].second.emplace_back(bottomright, spr->getColor(), tex_rect.bottomright());
            if (i == 0 && order == 0)
                m_global_bounds = rect;
            else {
                m_global_bounds.left = std::min(rect.left, m_global_bounds.left);
                m_global_bounds.top = std::min(rect.top, m_global_bounds.top);
                auto right = std::max(rect.right(), m_global_bounds.right());
                auto bottom = std::max(rect.bottom(), m_global_bounds.bottom());
                m_global_bounds.width = right - m_global_bounds.left;
                m_global_bounds.height = bottom - m_global_bounds.top;
            }
        }
    }
}

void SpriteBatch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& [texture, vector] : m_vertices) {
        states.texture = texture;
        target.draw(vector.data(), vector.size(), sf::PrimitiveType::Triangles, states);
    }
}
