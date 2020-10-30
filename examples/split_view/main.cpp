/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas.h>

/**
 * This example will show you how to create a split screen, which can be
 * used for 2 players games for example.
 * The idea is to create 2 independent cameras, each has a size of half the window
 * resolution and a viewport of 50% (0.5). These 2 cameras can look at the same scene,
 * this way they can render the same level but at a different position.
 */
class Game : public ns::App {
public:
    Game() : ns::App("Split View", 1080, 720) {
        // create a scene
        auto* scene = createScene("main");

        // adding some shapes to the scene
        auto* bg = new sf::RectangleShape({1080, 720});
        bg->setFillColor(sf::Color::White);
        scene->getDefaultLayer()->add(bg);

        for (int i = 0; i < 50; ++i) {
            auto* shape = new sf::CircleShape(20);
            shape->setOrigin(20, 20);
            shape->setPointCount(std::rand()%5+3);
            shape->setFillColor(sf::Color(std::rand()%25 * 10, std::rand()%25 * 10, std::rand()%25 * 10, 255));
            shape->setPosition(std::rand()%1080, std::rand()%720);
            shape->setOutlineColor(sf::Color::Black);
            shape->setOutlineThickness(1);
            scene->getDefaultLayer()->add(shape);
        }

        // creating 2 cameras each taking half the screen (viewport width of 0.5)
        auto* camera_left = createCamera("left", 0, {0, 0, 1080/2, 720}, {0, 0, 0.5, 1});
        camera_left->lookAt(scene);

        auto* camera_right = createCamera("right", 0, {0, 0, 1080/2, 720}, {0.5, 0, 0.5, 1});
        camera_right->lookAt(scene);

        // help text on separate scene
        createCamera("ui", 1)->lookAt(createScene("ui"));

        auto* txt = new sf::Text("Press WASD to move left camera or arrow keys to move right camera.", ns::Arial::getFont());
        txt->setCharacterSize(25);
        txt->setFillColor(sf::Color::Blue);
        txt->move(10, 10);
        getScene("ui")->getDefaultLayer()->add(txt);
    }

    void update() override {
        // move the left camera with WASD (or ZQSD for AZERTY keyboards)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            getCamera("left")->move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            getCamera("left")->move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            getCamera("left")->move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            getCamera("left")->move(0, 5);

        // move the right camera with the arrows
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            getCamera("right")->move(-5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            getCamera("right")->move(5, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            getCamera("right")->move(0, -5);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            getCamera("right")->move(0, 5);
    }
};

int main() {
    Game g;
    g.run();
    return 0;
}
