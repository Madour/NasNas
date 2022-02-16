/**
* Created by Modar Nasser on 26/04/2020.
**/

#pragma once

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Tilemapping.hpp>
#include <NasNas/Ecs.hpp>
#include <NasNas/Ui.hpp>

#include "Player.hpp"
#include "ShaderTransition.hpp"

class MouseParticleSystem : public ns::ParticleSystem {
    void onParticleCreate(ns::Particle& particle) override {
        auto s = ns::utils::getRandomFloat(1.f, 1.5f);
        auto a = ns::utils::getRandomFloat(0.f, 360.f);
        particle.rotation = a;
        particle.velocity.x = 1.2f * s*std::cos(ns::to_radian(a));
        particle.velocity.y = std::abs(s*std::sin(ns::to_radian(a)));
        particle.lifetime = ns::utils::getRandomFloat(1.f, 2.f);
    }
    void onParticleUpdate(ns::Particle& particle) override {
        particle.rotation += ns::utils::getRandomFloat(0.5f, 1.0f);
        particle.color.a = static_cast<int>((1.f-particle.getAge()/particle.lifetime)*255)&0xff;
        particle.velocity.y += 0.07f;
        particle.velocity.x -= 0.05f * (particle.velocity.x / std::abs(particle.velocity.x));
    }
};

class Game: public ns::App {
public:
    Game();
    ~Game() override;

    void onEvent(const sf::Event& event) override ;
    void update() override ;

private:
    ns::BitmapFont font;

    ns::tm::TiledMap tiled_map;

    Player player;
    std::vector<sf::CircleShape> shapes;

    MouseParticleSystem particle_system;

    sf::Shader* palette_shader;
    int frame_counter = 0;
};
