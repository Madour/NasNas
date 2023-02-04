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
    void setup() override;
    void update() override;
};

struct GameStateTwo : ns::AppState, ns::AppAccess<Game> {
    void setup() override;
    void update() override;
};


Game::Game() : ns::StateStackApp("State Stack App example", {720, 480}) {
    ns::Settings::debug_mode.show_bounds = false;
    ns::Settings::debug_mode = true;

    auto* text1 = new sf::Text("State One", ns::Arial::getFont(), 60);
    text1->setPosition(360 - text1->getGlobalBounds().width / 2, 200);

    auto* text2 = new sf::Text("State Two", ns::Arial::getFont(), 60);
    text2->setPosition(360 - text2->getGlobalBounds().width / 2, 200);

    auto& scene1 = createScene("one");
    auto& scene2 = createScene("two");
    createCamera("main", 0);

    scene1.getDefaultLayer().add(text1);
    scene2.getDefaultLayer().add(text2);

    pushState<GameStateOne>();

    addDebugText("Press the space bar to change the current state", {20, 20});
}


void GameStateOne::setup() {
    app().getWindow().setClearColor(sf::Color(200, 230, 250));
    app().getCamera("main").lookAt(app().getScene("one"));
}

void GameStateOne::update() {
    if (ns::Inputs::isKeyPressed(sf::Keyboard::Space) && !app().isRunningTransition()) {
        // when space bar is pressed, go to StateTwo
        app().pushState<GameStateTwo>();
    }
}

void GameStateTwo::setup() {
    app().getWindow().setClearColor(sf::Color(250, 200, 180));
    app().getCamera("main").lookAt(app().getScene("two"));
}

void GameStateTwo::update() {
    if (ns::Inputs::isKeyPressed(sf::Keyboard::Space) && !app().isRunningTransition()) {
        // when space bar is pressed, create a new CircleClose transition, then pop the state to go back to state one
        app().startTransition<ns::transition::CircleClose>(500).onEnd([&]() {
            app().popState();
            app().startTransition<ns::transition::CircleOpen>(500);
        });
    }
}


int main() {
    ns::AppConfig config;
    config.window_style = sf::Style::Close;
    ns::Settings::setConfig(config);

    Game g;
    g.run();
}
