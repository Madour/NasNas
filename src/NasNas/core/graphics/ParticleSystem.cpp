// Created by Modar Nasser on 14/02/2021.

#include "NasNas/core/graphics/ParticleSystem.hpp"

using namespace ns;

void ParticleSystem::setTexture(const sf::Texture& texture) {
    m_texture = &texture;
}

void ParticleSystem::setEmmitRate(float rate) {
    m_rate = rate;
}

void ParticleSystem::emmit(const sf::IntRect& rect, int nb, bool repeat) {
    for (int i = 0; i < nb; ++i) {
        m_particles.emplace_back();
        auto& particle = m_particles.back();
        onParticleCreate(particle);
        particle.lifetime = 0.f;
        particle.clock.restart();
        particle.repeat = repeat;
        particle.sprite.setTexture(*m_texture);
        particle.sprite.setTextureRect(rect);
        particle.sprite.setPosition(m_position);
        particle.sprite.setOrigin(rect.width/2, rect.height/2);
    }
}

auto ParticleSystem::getParticleCount() -> unsigned {
    return m_particles.size();
}

void ParticleSystem::setPosition(float x, float y) {
    m_position = {x, y};
}

void ParticleSystem::setPosition(const sf::Vector2f& pos) {
    m_position = pos;
}

auto ParticleSystem::getPosition() const -> sf::Vector2f {
    return m_position;
}

auto ParticleSystem::getGlobalBounds() const -> ns::FloatRect {
    return m_batch.getGlobalBounds();
}

void ParticleSystem::update() {
    auto elapsed = m_clk.getElapsedTime().asSeconds();
    m_to_emmit += elapsed*m_rate;

    m_batch.clear();
    for (auto it = m_particles.begin(); it != m_particles.end();) {
        auto& particle = *it;
        if (particle.getAge() < particle.lifetime) {
            onParticleUpdate(particle);
            particle.sprite.move(particle.velocity);
            particle.sprite.setScale(particle.scale, particle.scale);
            particle.sprite.setRotation(particle.rotation);
            particle.sprite.setColor(particle.color);
            m_batch.draw(&particle.sprite);
            it++;
            continue;
        }
        if (particle.repeat || particle.lifetime == 0.f) {
            if (m_to_emmit > 1.f) {
                m_to_emmit -= 1.f;
                onParticleCreate(particle);
                particle.clock.restart();
            }
            particle.sprite.setPosition(m_position);
            it++;
        }
        else {
            it = m_particles.erase(it);
        }
    }
    m_batch.end();
    m_clk.restart();
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_batch, states);
}
