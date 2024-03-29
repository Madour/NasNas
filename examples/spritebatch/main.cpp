/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

/**
 * This example shows how to create a spritebatch
 * to render a lot of sprites very fast.
 * SpriteBatch can batch sprites with different textures.
 */
class Game : public ns::App {

    std::vector<std::unique_ptr<ns::Sprite>> m_sprites;
    ns::SpriteBatch m_spritebatch;

public:
    Game() : ns::App("Spritebatch example", {1280, 720}) {
        ns::Settings::debug_mode = true;

        // get the texture
        auto& texture = ns::Res::getTexture("adventurer.png");

        // start the batch. SpriteBatch uses a VertexBuffer, can be either Stream, Dynamic or Static.
        // Stream is for sprites that change every frame (default)
        // Dynamic is for sprites that change sometimes
        // Static is for sprites that never change.
        m_spritebatch.start(sf::VertexBuffer::Stream);

        // create 1000 random sprites, and draw them in the batch
        for (int i = 0; i < 1000; ++i) {
            m_sprites.emplace_back(new ns::Sprite(texture, {0, 0, 50, 37}));
            auto& sprite = m_sprites.back();
            sprite->setOrigin(25, 18.5);
            sprite->setPosition(rand()%1280, rand()%720);
            sprite->setColor(sf::Color(rand()%255, rand()%255, rand()%255));
            sprite->setScale(1.5f, 1.5f);
            m_spritebatch.draw(sprite.get());
        }
        // alternatively, you can draw sprites in the batch directly like this
        /*
        for (int i = 0; i < 1000; ++i)
            m_spritebatch->draw(&texture, sf::Vector2f(rand()%1280, rand()%720), {0, 0, 50, 37});
        */

        // don't forget to end the batch when finished drawing in the batch !
        m_spritebatch.end();

        // create a scene
        auto& scene = createScene("main");
        // add the batch to the scene
        scene.getDefaultLayer().addRaw(&m_spritebatch);
        // setup camera
        createCamera("main", 0).lookAt(scene);

        // add some debug texts
        ns::DebugTextInterface::outline_color = sf::Color::Black;
        addDebugText<unsigned>("Sprites number : ", [&]{return m_sprites.size();}, {10, 10});
        addDebugText<int>("Draw calls : ", [&]{return m_spritebatch.getDepth();}, {10, 40});
        addDebugText("Left Click to add 100 additional sprites to the batch", {300, 10});
        addDebugText("Right Click to clear sprite batch", {300, 40});
    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);

        if (event.type == sf::Event::MouseButtonPressed) {
            // on user left click
            if (event.mouseButton.button == sf::Mouse::Button::Left) {
                // add 100 more randomized sprites to the batch !
                for (unsigned i = 0; i < 100; ++i) {
                    auto& texture = ns::Res::getTexture("adventurer.png");
                    m_sprites.emplace_back(new ns::Sprite(texture, {0, 0, 50, 37}));
                    auto& spr = m_sprites.back();
                    spr->setRotation(rand()%360);
                    spr->setPosition(rand()%1280, rand()%720);
                    spr->setColor(sf::Color(rand()%255, rand()%255, rand()%255));
                    float scale = (rand()%100)/100.f;
                    spr->setScale(1.f + scale, 1.f + scale);

                    m_spritebatch.draw(spr.get());
                }
                m_spritebatch.end();
            }
            // on user right click
            else if (event.mouseButton.button == sf::Mouse::Button::Right) {
                // delete all sprites
                m_spritebatch.clear();
                m_sprites.clear();
            }

        }
    }

    void update() override {
        // update the sprites here (rotation, translation, scale ...)
        for (auto& sprite : m_sprites) {
            sprite->rotate(1);
        }
    }
};

int main() {
    ns::Res::load("assets");

    ns::AppConfig config;
    config.frame_rate = 0; // unlock FPS
    ns::Settings::setConfig(config);

    Game g;
    g.run();

    ns::Res::dispose();
    return 0;
}
