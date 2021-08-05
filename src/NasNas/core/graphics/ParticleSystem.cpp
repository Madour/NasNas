// Created by Modar Nasser on 14/02/2021.

#include "NasNas/core/graphics/ParticleSystem.hpp"
#include "NasNas/core/data/Config.hpp"

using namespace ns;

void ParticleSystem::setTexture(const sf::Texture& texture) {
    m_texture = &texture;
}

void ParticleSystem::setEmitRate(float rate) {
    m_rate = rate;
}

void ParticleSystem::emit(const sf::IntRect& rect, int nb, bool repeat) {
    m_batch.setDrawOrder(SpriteBatch::DrawOrder::Back);
    m_particles.reserve(m_particles.size()+nb);
    for (int i = 0; i < nb; ++i) {
        auto& particle = *m_particles.emplace_back(new Particle());
        onParticleCreate(particle);
        particle.repeat = repeat;
        particle.sprite.setTexture(*m_texture);
        particle.sprite.setTextureRect(rect);
        particle.sprite.setPosition(m_position);
        particle.sprite.setOrigin(rect.width/2.f, rect.height/2.f);
        particle.sprite.setColor(sf::Color(255, 255, 255, 0));
        m_batch.draw(&particle.sprite);
    }
    m_batch.end();
}

void ParticleSystem::emitBurst(const sf::IntRect& rect, int nb) {
    m_batch.setDrawOrder(SpriteBatch::DrawOrder::Front);
    m_particles.reserve(m_particles.size()+nb);
    for (int i = 0; i < nb; ++i) {
        auto& particle = *m_particles.emplace_back(new Particle());
        onParticleCreate(particle);
        particle.active = true;
        particle.repeat = false;
        particle.sprite.setTexture(*m_texture);
        particle.sprite.setTextureRect(rect);
        particle.sprite.setPosition(m_position);
        particle.sprite.setOrigin(rect.width/2.f, rect.height/2.f);
        particle.sprite.setColor(sf::Color(255, 255, 255, 0));
        m_batch.draw(&particle.sprite);
    }
    m_batch.end();
    m_count += nb;
}

auto ParticleSystem::getParticleCount() const -> unsigned {
    return m_count;
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
    float dt = 1.f/ns::Settings::getConfig().update_rate;
    m_to_emmit = std::min(m_rate, m_to_emmit+m_rate*dt);

    for (auto it = m_particles.begin(); it != m_particles.end();) {
        auto& particle = **it;

        if (particle.age >= particle.lifetime) {
            if (particle.repeat) {
                particle.sprite.setPosition(m_position);
                particle.sprite.setColor(sf::Color(255, 255, 255, 0));
                particle.age = 0;
                particle.active = false;
                it++;
            }
            else {
                m_batch.erase(&particle.sprite);
                it = m_particles.erase(it);
            }
            m_count--;
        }
        else {
            if (particle.active) {
                updateParticle(particle, dt); // update particle data
            }
            else {
                particle.sprite.setPosition(m_position);
                if (m_to_emmit > 1.f){
                    particle.active = true;
                    particle.sprite.setColor(sf::Color::White);
                    onParticleCreate(particle);
                    updateParticle(particle, 0);
                    m_to_emmit -= 1.f;
                    m_count++;
                }
            }
            it++;
        }
    }
}

void ParticleSystem::updateParticle(Particle& particle, float dt) {
    onParticleUpdate(particle);
    particle.age = particle.age+dt;
    // update particle sprite
    particle.sprite.move(particle.velocity);
    particle.sprite.setScale(particle.scale, particle.scale);
    particle.sprite.setRotation(particle.rotation);
    particle.sprite.setColor(particle.color);
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_batch, states);
}
