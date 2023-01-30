// Created by Modar Nasser on 14/02/2022.

#include <NasNas/Core.hpp>

/**
 * \brief This example shows how to create a StateStackApp.
 * pushState method is used to add a new state to the app.
 * popState method is used to delete current state and go to
 * the previous one.
 * Be careful to manage your scene layers and cameras correctly
 * using the setup method !
 */

class Game : public ns::StateStackApp {
public:
    Game();
};

struct GameStateOne : ns::AppState, ns::AppAccess<Game> {
    GameStateOne();
    void setup() override;
    void update() override;
};

struct GameStateTwo : ns::AppState, ns::AppAccess<Game> {
    GameStateTwo();
    void setup() override;
    void update() override;
};


Game::Game() : ns::StateStackApp("State Stack App example", {720, 480}) {
    ns::Settings::debug_mode.show_bounds = false;
    ns::Settings::debug_mode = true;

    createScene("one");
    createScene("two");
    createCamera("main", 0).lookAt(getScene("one"));

    pushState<GameStateOne>();

    addDebugText("Press the space bar to change the current state", {20, 20});
}


GameStateOne::GameStateOne() {
    auto* text = new sf::Text("State One", ns::Arial::getFont(), 60);
    text->setPosition(360 - text->getGlobalBounds().width / 2, 200);
    app().getScene("one").getDefaultLayer().add(text);
}

void GameStateOne::setup() {
    app().getWindow().setClearColor(sf::Color(200, 230, 250));
    app().getCamera("main").lookAt(app().getScene("one"));
}

void GameStateOne::update() {
    if (ns::Inputs::isKeyPressed(sf::Keyboard::Space)) {
        // when space bar is pressed, go to StateTwo
        app().pushState<GameStateTwo>();
    }
}

GameStateTwo::GameStateTwo() {
    auto* text = new sf::Text("State Two", ns::Arial::getFont(), 60);
    text->setPosition(360 - text->getGlobalBounds().width / 2, 200);
    app().getScene("two").getDefaultLayer().add(text);
}

void GameStateTwo::setup() {
    app().getWindow().setClearColor(sf::Color(250, 200, 180));
    app().getCamera("main").lookAt(app().getScene("two"));
}

void GameStateTwo::update() {
    if (ns::Inputs::isKeyPressed(sf::Keyboard::Space)) {
        // when space bar is pressed, create a new CircleClose transition and start it
        auto* tr = new ns::transition::CircleClose(500);
        tr->onEnd([&]{
            // when the transition ends, popState and start a new CircleOpen transition
            app().popState();
            (new ns::transition::CircleOpen(500))->start();
        });
        tr->start();
    }
}


int main() {
    ns::AppConfig config;
    config.window_style = sf::Style::Close;
    ns::Settings::setConfig(config);

    Game g;
    g.run();
}
