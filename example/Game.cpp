/**
* Created by Modar Nasser on 26/04/2020.
**/

#include "Game.hpp"

#include "Sprites.hpp"

Game::Game() :
ns::App("NasNas++ demo", 1080, 720, 1080/2, 720/2)
{
    // creating the scene
    this->scene = this->createScene(1600, 900);

    // creating background layer
    this->scene->addLayer(std::make_shared<ns::Layer>("background"), 0);

    // creating a RectangleShape, fill it in Black color and adding it to the background layer
    auto rect2 = std::make_shared<sf::RectangleShape>(sf::Vector2f(1600, 900));
    rect2->setFillColor(sf::Color::Black);
    this->scene->getLayer(0)->add(rect2);

    // creating shapes layer
    this->scene->addLayer(std::make_shared<ns::Layer>("shapes"), 1);

    auto colors = std::vector<sf::Color>{sf::Color::Blue, sf::Color::Red, sf::Color::Green,
                                         sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta,
                                         sf::Color::White};
    // generating 100 random octogons and adding them to the shapes layer
    for (int i = 0; i < 100; ++i) {
        auto shape = std::make_shared<sf::CircleShape>(20.0f);
        shape->setPointCount(8);
        shape->setFillColor(colors.at(i%colors.size()));
        shape->setOutlineColor(sf::Color::Black);
        shape->setOutlineThickness(1);
        shape->setOrigin(20, 20);
        shape->setPosition((float)(std::rand()%1600), (float)(std::rand()%900));
        this->scene->getLayer(1)->add(shape);
    }

    // creating entities layer
    auto entities_layer = std::make_shared<ns::Layer>("entities_layer");
    this->scene->addLayer(entities_layer, 2);

    auto* game_sprites = new Sprites();
    // creating an entity and setting its position
    this->player = std::make_shared<ns::BaseEntity>("Player", &game_sprites->player_spr);
    this->player->setPosition({100, 100});

    // adding the entity to the layer
    this->scene->getLayer(2)->add(this->player);

    // adding debug texts
    // directly using addDebugText to create automatically a DebugText object
    this->addDebugText<sf::Vector2f>(this->player.get(), &ns::BaseEntity::getPosition, "position:", {10, 10}, sf::Color::Green);
    this->addDebugText<sf::Vector2f>(this->player.get(), &ns::BaseEntity::getVelocity, "velocity:", {10, 50});
    // by creating manually a DebugText object, changing its properties and adding it to the app
    auto* dbg_txt = new ns::DebugText<float>(this->player.get(), &ns::BaseEntity::getY, "pos_y:", {500, 10});
    dbg_txt->setFillColor(sf::Color::Black);
    dbg_txt->setOutlineThickness(1);
    dbg_txt->setOutlineColor(sf::Color::White);
    this->addDebugText(dbg_txt);

    // telling the camera to look at the scene
    this->game_camera->lookAt(this->scene);
    // telling the camera to follow our entity
    this->game_camera->follow(*this->player);
    // the camera will have 10 frames delay
    this->game_camera->setFramesDelay(10);
}

void Game::update() {
    // moving the player
    if(!this->getInputs().empty())
        switch (this->getInputs().at(0)) {
            case sf::Keyboard::Left:
                player->move(-10, 0);
                break;
            case sf::Keyboard::Right:
                player->move(10, 0);
                break;
            case sf::Keyboard::Up:
                player->move(0, -10);
                break;
            case sf::Keyboard::Down:
                player->move(0, 10);
                break;
            default:
                break;
        }

    // moving the octogons randomly
    for (const auto& drawable: this->scene->getLayer(1)->getDrawables()) {
        std::visit([&](auto&& arg){arg->move(std::rand()%3 -1, std::rand()%3 -1);}, drawable);
    }

    // updating the player entity
    this->player->update();

    // sorting the shapes layer by the y position
    this->scene->getLayer(1)->ySort();
}

void Game::onEvent(sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
            this->getWindow().close();
            break;

        case sf::Event::KeyReleased:
            if(event.key.code == sf::Keyboard::F)
                this->toggleFullscreen();
            if (event.key.code == sf::Keyboard::Escape)
                this->getWindow().close();
            break;

        default:
            break;
    }
}

Game::~Game() = default;

