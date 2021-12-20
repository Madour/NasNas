/**
* Created by Modar Nasser on 07/06/2020.
**/

#pragma once

#include <cmath>

#include <SFML/Audio.hpp>

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Ecs.hpp>

class Player : public ns::EntityObject, public sf::Drawable {
public:
    Player();
    void update();
    void jump();
    void moveLeft();
    void moveRight();

    auto getPosition() const -> sf::Vector2f;
    auto getGlobalBounds() const -> ns::FloatRect;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::unique_ptr<ns::Spritesheet> m_spritesheet = nullptr;
    bool m_double_jump = false;
    bool m_in_air = false;
    bool m_must_land = false;

    sf::SoundBuffer m_jump_sound_buffer;
    sf::Sound m_jump_sound;
    sf::SoundBuffer m_walk_sound_buffer;
    sf::Sound m_walk_sound;
};

