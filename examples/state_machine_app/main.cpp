// Created by Modar Nasser on 06/09/2021.

#include <NasNas/Core.hpp>

/**
 * \brief This example shows how to create a StateMachineApp.
 * Two states are declared and the setState method is used to go from
 * one state to the other with or without using a Transition.
 */

class Game : public ns::StateMachineApp {
public:
    Game();
};

struct GameStateOne : ns::AppState, ns::AppAccess<Game> {
    GameStateOne();
    void onEvent(const sf::Event&) override;
};

struct GameStateTwo : ns::AppState, ns::AppAccess<Game> {
    GameStateTwo();
    void onEvent(const sf::Event&) override;
};


Game::Game() : ns::StateMachineApp("State Machine App example", {720, 480}) {
    ns::Settings::debug_mode.show_bounds = false;
    ns::Settings::debug_mode = true;

    createScene("main");
    createCamera("main", 0).lookAt(getScene("main"));

    setState<GameStateOne>();

    addDebugText("Press the space bar to change the current state", {20, 20});
}


GameStateOne::GameStateOne() {
    app().getWindow().setClearColor(sf::Color(200, 230, 250));

    auto& scene = app().getScene("main");
    scene.getDefaultLayer().clear();

    auto* text = new sf::Text("State One", ns::Arial::getFont(), 60);
    text->setPosition(360 - text->getGlobalBounds().width / 2, 200);
    scene.getDefaultLayer().add(text);
}

void GameStateOne::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            if (!app().isRunningTransition()) {
                // when space bar is pressed, go to StateTwo
                app().setState<GameStateTwo>();
            }
        }
    }
}

GameStateTwo::GameStateTwo() {
    app().getWindow().setClearColor(sf::Color(250, 200, 180));

    auto& scene = app().getScene("main");
    scene.getDefaultLayer().clear();

    auto* text = new sf::Text("State Two", ns::Arial::getFont(), 60);
    text->setPosition(360 - text->getGlobalBounds().width / 2, 200);
    scene.getDefaultLayer().add(text);
}

void GameStateTwo::onEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && !app().isRunningTransition()) {
        if (event.key.code == sf::Keyboard::Space) {
            if (!app().isRunningTransition()) {
                // when space bar is pressed, create a new CircleClose transition, then set app state one
                app().startTransition<ns::transition::CircleClose>(500).onEnd([&]() {
                    app().setState<GameStateOne>();
                    app().startTransition<ns::transition::CircleOpen>(500);
                });
            }
        }
    }
}


int main() {
    ns::AppConfig config;
    config.window_style = sf::Style::Close;
    ns::Settings::setConfig(config);

    Game g;
    g.run();
}
