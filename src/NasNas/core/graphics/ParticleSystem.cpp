// Created by Modar Nasser on 14/02/2021.

#include "NasNas/core/graphics/ParticleSystem.hpp"
#include "NasNas/core/data/Config.hpp"

using namespace ns;

void ParticleSystem::setTexture(const sf::Texture& texture) {
    m_texture = &texture;
}

void ParticleSystem::setEmmitRate(float rate) {
    m_rate = rate;
}

void ParticleSystem::emmit(const sf::IntRect& rect, int nb, bool repeat) {
    m_particles.reserve(m_particles.size()+nb);
    for (int i = 0; i < nb; ++i) {
        m_particles.emplace_back(new Particle());
        auto& particle = m_particles.back();
        onParticleCreate(*particle);
        particle->repeat = repeat;
        particle->sprite.setTexture(*m_texture);
        particle->sprite.setTextureRect(rect);
        particle->sprite.setPosition(m_position);
        particle->sprite.setOrigin(rect.width/2.f, rect.height/2.f);
        particle->sprite.setColor(sf::Color(255, 255, 255, 0));
        m_batch.draw(&particle->sprite);
    }
    m_batch.end();
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
    float dt = 1.f/ns::Config::Window::update_rate;
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
                // update particle data
                onParticleUpdate(particle);
                particle.age = particle.age+dt;
                // update particle sprite
                particle.sprite.move(particle.velocity);
                particle.sprite.setScale(particle.scale, particle.scale);
                particle.sprite.setRotation(particle.rotation);
                particle.sprite.setColor(particle.color);
            }
            else {
                if (m_to_emmit > 1.f){
                    particle.active = true;
                    particle.sprite.setColor(sf::Color::White);
                    onParticleCreate(particle);
                    m_to_emmit -= 1.f;
                    m_count++;
                }
                particle.sprite.setPosition(m_position);
            }
            it++;
        }
    }
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_batch, states);
}
