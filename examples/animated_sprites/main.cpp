// Created by Modar Nasser on 23/12/2021.

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

/**
 * This example shows how to create animated sprites
 * using SpriteSheet, Sprite and AnimPlayer
 */
class Game : public ns::App {

    ns::SpriteSheet m_spritesheet;
    std::array<sf::Sprite, 8> m_sprites;
    std::array<ns::AnimPlayer, 8> m_animators;

public:
    Game() {
        ns::Settings::debug_mode = false;
        auto& texture = ns::Res::getTexture("adventurer.png");

        // set up the sprite sheet by defining the texture and the grid dimensions
        m_spritesheet.setTexture(texture);
        m_spritesheet.setGrid({50, 37}, 7);

        // add the animations
        // <name>, <first_frame_index>, <frames_number>, <frame_duration>
        m_spritesheet.addAnim("idle", 0, 4, 120);
        m_spritesheet.addAnim("run", 8, 6, 100);
        m_spritesheet.addAnim("slide", 24, 3, 130);
        m_spritesheet.addAnim("climb", 81, 4, 100);
        m_spritesheet.addAnim("slash_up", 41, 6, 100);
        m_spritesheet.addAnim("slash_down", 47, 6, 100);
        m_spritesheet.addAnim("slash_front", 53, 6, 100);
        m_spritesheet.addAnim("magic", 85, 9, 120);

        m_animators[0].play(m_spritesheet.getAnim("idle"));
        m_animators[1].play(m_spritesheet.getAnim("run"));
        m_animators[2].play(m_spritesheet.getAnim("slide"));
        m_animators[3].play(m_spritesheet.getAnim("climb"));
        m_animators[4].play(m_spritesheet.getAnim("slash_up"));
        m_animators[5].play(m_spritesheet.getAnim("slash_down"));
        m_animators[6].play(m_spritesheet.getAnim("slash_front"));
        m_animators[7].play(m_spritesheet.getAnim("magic"));

        for (unsigned i = 0; i < m_sprites.size(); ++i) {
            auto& sprite = m_sprites[i];
            sprite.setTexture(*m_spritesheet.getTexture());
            sprite.setPosition(30 + (i % 4) * 70, 30 + (i / 4) * 60);
        }

        // create scene & camera
        auto& scene = createScene("main");
        createCamera("main", 0).lookAt(scene);

        for (auto& sprite: m_sprites) {
            scene.getDefaultLayer().add(sprite);
        }
    }

    void update() override {
        // update the sprites
        for (unsigned i = 0; i < m_animators.size(); ++i) {
            m_animators[i].update(m_sprites[i]);
        }
    }
};

int main() {
    ns::Res::load("assets");

    ns::AppConfig config;
    config.title = "Animated sprites example";
    config.resolution = {320, 180};
    config.scale = 4;
    ns::Settings::setConfig(config);

    Game g;
    g.run();

    ns::Res::dispose();
    return 0;
}
