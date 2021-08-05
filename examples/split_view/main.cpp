/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas/Core.hpp>

/**
 * This example will show you how to create a split screen, which can be
 * used for 2 players games for example.
 * The idea is to create 2 independent cameras, each has a size of half the window
 * resolution and a viewport of 50% (0.5). These 2 cameras can look at the same scene,
 * this way they can render the same level but at a different position.
 */
class Game : public ns::App {
public:
    Game() : ns::App("Split View", {1080*2, 720*2}, 0.5f) {
        // create a scene
        auto& scene = createScene("main");

        sf::Vector2i resolution{getWindow().getAppView().getSize()};
        sf::Vector2i window_size{getWindow().getSize()};

        // adding some shapes to the scene
        auto* bg = new sf::RectangleShape(getWindow().getAppView().getSize());
        bg->setFillColor(sf::Color::White);
        scene.getDefaultLayer().add(bg);

        for (int i = 0; i < 100; ++i) {
            auto* shape = new sf::CircleShape(20);
            shape->setOrigin(20, 20);
            shape->setPointCount(std::rand()%5+3);
            shape->setFillColor(sf::Color(std::rand()%25 * 10, std::rand()%25 * 10, std::rand()%25 * 10, 255));
            shape->setPosition(std::rand()%resolution.x, std::rand()%resolution.y);
            shape->setOutlineColor(sf::Color::Black);
            shape->setOutlineThickness(1);
            scene.getDefaultLayer().add(shape);
        }

        // creating 2 cameras each taking half the screen (viewport width of 0.499 to let a black line separator)
        auto& camera_left = createCamera("left", 0, {0, 0, window_size.x/2, window_size.y}, {0, 0, 0.499f, 1});
        camera_left.lookAt(scene);

        auto& camera_right = createCamera("right", 0, {0, 0, window_size.x/2, window_size.y}, {0.501f, 0, 0.499f, 1});
        camera_right.lookAt(scene);

        addDebugText("Press WASD to move left camera or arrow keys to move right camera.", {50, 10});
    }

    void update() override {
        // move the left camera with WASD (or ZQSD for AZERTY keyboards)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            getCamera("left").move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            getCamera("left").move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            getCamera("left").move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            getCamera("left").move(0, 5);

        // move the right camera with the arrows
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            getCamera("right").move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            getCamera("right").move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            getCamera("right").move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            getCamera("right").move(0, 5);
    }
};

int main() {
    ns::Settings::debug_mode = true;
    ns::Settings::debug_mode.show_bounds = false;

    Game g;
    g.run();

    return 0;
}
