// Created by Modar Nasser on 14/02/2021.

#include "NasNas/core/graphics/ParticleSystem.hpp"

using namespace ns;

void ParticleSystem::setTexture(const sf::Texture& texture) {
    m_texture = &texture;
}

void ParticleSystem::emmit(const sf::IntRect& rect, int nb, bool repeat) {
    for (int i = 0; i < nb; ++i) {
        m_particles.emplace_back();
        auto& particle = m_particles.back();
        onParticleCreate(particle);
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
    for (auto it = m_particles.begin(); it != m_particles.end();) {
        auto& particle = *it;
        onParticleUpdate(particle);
        particle.sprite.move(particle.velocity);
        particle.sprite.setScale(particle.scale, particle.scale);
        particle.sprite.setRotation(particle.rotation);
        particle.sprite.setColor(particle.color);
        if (particle.getAge() > particle.lifetime) {
            if (particle.repeat) {
                particle.sprite.setPosition(m_position);
                particle.clock.restart();
                onParticleCreate(particle);
                it++;
            }
            else {
                it = m_particles.erase(it);
            }
        }
        else it++;
    }
    m_batch.clear();
    for (auto& particle : m_particles) {
        m_batch.draw(&particle.sprite);
    }
    m_batch.end();
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_batch, states);
}
