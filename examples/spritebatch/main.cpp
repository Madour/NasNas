/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas.h>

/**
 * This example shows how to create a spritebatch
 * to render a lot of sprite very fast
 */
class Game : public ns::App {
std::vector<sf::Sprite> m_sprites;
public:
    Game() : ns::App("Spritebatch", 1080, 720) {
        // get the texture
        auto& texture = ns::Res::getTexture("adventurer.png");

        // create a spritebatch
        auto* sprite_batch = new ns::SpriteBatch("my_batch");

        // create 10k sprites and draw them in the batch
        m_sprites.resize(10000);
        for (auto& sprite : m_sprites) {
            sprite.setTexture(texture);
            sprite.setTextureRect({0, 0, 50, 37});
            sprite.setPosition(rand()%1080, rand()%720);
            sprite_batch->draw(&sprite);
        }

        // alternatively, you can draw sprites in the batch directly like this :
        /*
        for (int i = 0; i < 10000; ++i)
            sprite_batch->draw(&texture, sf::Vector2f(rand()%1080, rand()%720), {0, 0, 50, 37});
        sprite_batch->end();
        */

        // create a scene
        auto* scene = createScene("main");
        // add the batch to the scene
        scene->getDefaultLayer()->add(sprite_batch);
        // setup camera
        createCamera("main", 0)->lookAt(scene);
    }

    void update() override {
        // update your sprites here (rotation, translation, scale ...)
        /*
        for (auto& sprite : m_sprites) {
            sprite.rotate(1);
        }
        */
    }
};

int main() {
    ns::Res::load("assets");
    ns::Config::Window::framerate_limit = 0;
    Game g;
    g.run();
    ns::Res::dispose();
    return 0;
}
