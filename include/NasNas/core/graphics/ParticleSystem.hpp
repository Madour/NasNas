// Created by Modar Nasser on 14/02/2021.

#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "NasNas/core/graphics/SpriteBatch.hpp"

namespace ns {
    class ParticleSystem;

    struct Particle {
        float rotation=0.f;
        float scale=1.f;
        sf::Vector2f velocity={0.f,0.f};
        sf::Color color = sf::Color::White;
        float lifetime;
    private:
        friend ParticleSystem;
        bool repeat = false;
        sf::Sprite sprite;
    };

    class ParticleSystem : public ns::Drawable {
    public:
        ParticleSystem() = default;

        void setTexture(const sf::Texture& texture);
        void emmit(const sf::IntRect& rect, int nb, bool repeat=false);
        auto createParticle(const sf::IntRect& rect, bool repeat=false) -> Particle&;

        auto getParticleCount() -> unsigned;

        void setPosition(float x, float y);
        void setPosition(const sf::Vector2f& pos);
        auto getPosition() const -> sf::Vector2f override;
        auto getGlobalBounds() const -> ns::FloatRect override;

        virtual void onParticleCreate(Particle& particle) = 0;
        virtual void onParticleUpdate(Particle& particle) = 0;
        virtual bool isParticleDead(Particle& particle) = 0;

        void update();
        static auto getRandomFloat(float min=0.f, float max=1.f) -> float;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        const sf::Texture* m_texture = nullptr;
        sf::Vector2f m_position;
        std::vector<Particle> m_particles;
        ns::SpriteBatch m_batch;
    };

}

