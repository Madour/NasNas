// Created by Modar Nasser on 14/02/2021.

#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "NasNas/core/graphics/SpriteBatch.hpp"

namespace ns {
    class ParticleSystem;

    struct Particle {
        float rotation          = 0.f;
        float scale             = 1.f;
        sf::Vector2f velocity   = {0.f,0.f};
        sf::Color color         = sf::Color::White;
        float lifetime          = 1.f;
        auto getAge() const -> float { return age; }
    private:
        friend ParticleSystem;
        bool active = false;
        bool repeat = false;
        float age   = 0.f;
        ns::Sprite sprite;
    };

    class ParticleSystem : public sf::Drawable {
    public:
        ParticleSystem() = default;

        void setTexture(const sf::Texture& texture);
        void setEmitRate(float rate);
        void emit(const sf::IntRect& rect, int nb, bool repeat=false);
        void emitBurst(const sf::IntRect& rect, int nb);

        auto getParticleCount() const -> unsigned;

        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& pos);
        auto getPosition() const -> sf::Vector2f;
        auto getGlobalBounds() const -> ns::FloatRect;

        virtual void onParticleCreate(Particle& particle) = 0;
        virtual void onParticleUpdate(Particle& particle) = 0;

        void update();

    private:
        void updateParticle(Particle& particle, float dt);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        const sf::Texture* m_texture = nullptr;
        sf::Vector2f m_position;
        std::vector<std::unique_ptr<Particle>> m_particles;
        float m_rate = 9999.f;
        float m_to_emmit = 0.f;
        unsigned m_count = 0;
        ns::SpriteBatch m_batch;
    };

}

