/**
* Created by Modar Nasser on 26/04/2020.
**/

#include "Game.hpp"

#include "Player.hpp"

Game::Game() :
ns::App("NasNas++ demo", 1080, 720, 1080/2, 720/2, 60, 60) {
    // mapping keys inputs
    ns::Config::Inputs::setButtonKey("left", sf::Keyboard::Left);
    ns::Config::Inputs::setButtonKey("right", sf::Keyboard::Right);
    ns::Config::Inputs::setButtonKey("up", sf::Keyboard::Up);
    ns::Config::Inputs::setButtonKey("down", sf::Keyboard::Down);
    ns::Config::Inputs::setButtonKey("fullscreen", sf::Keyboard::F);

    // configuring physics constants
    ns::Config::Physics::gravity = 0;

    // creating the scene
    this->scene = this->createScene("main");

    // creating background layer
    this->scene->addLayer(new ns::Layer("background"), 0);

    // creating a RectangleShape, fill it in Grey color and adding it to the background layer
    auto rect2 = std::make_shared<sf::RectangleShape>(sf::Vector2f(2500, 2000));
    rect2->setFillColor(sf::Color(150, 150, 150));
    this->scene->getLayer(0)->add(rect2);

    // creating shapes layer
    this->scene->addLayer(new ns::Layer("shapes"), 1);

    auto colors = std::vector<sf::Color>{sf::Color::Blue, sf::Color::Red, sf::Color::Green,
                                         sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta,
                                         sf::Color::White};
    // generating 100 random octogons and adding them to the shapes layer
    for (int i = 0; i < 10000; ++i) {
        auto shape = std::make_shared<sf::CircleShape>(20.0f);
        shape->setPointCount(8);
        shape->setFillColor(colors.at(i%colors.size()));
        shape->setOutlineColor(sf::Color::Black);
        shape->setOutlineThickness(1);
        shape->setOrigin(20, 20);
        shape->setPosition((float)(std::rand()%2500), (float)(std::rand()%2000));
        this->scene->getLayer(1)->add(shape);
    }

    // creating entities layer
    auto entities_layer = std::make_shared<ns::Layer>("entities");
    this->scene->addLayer(entities_layer, 2);

    // creating an entity and setting its position
    this->player = std::make_shared<Player>();
    this->player->setPosition({100, 100});
    // adding the entity to the layer
    this->scene->getLayer("entities")->add(this->player);

    // creating BitmapFont
    auto bmp_font = std::make_shared<ns::BitmapFont>(
        ns::Res::get().getTexture("font"),
        sf::Vector2i(8, 8),
        " ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        std::unordered_map<char, int>({{'I', 7}, {'L', 7}})
    );
    // creating a BitmapText using the font created above
    auto bmp_text = std::make_shared<ns::BitmapText>("THIS IS A BITMAP TEXT CREATED FROM PNG FONT", bmp_font);
    bmp_text->setPosition(sf::Vector2f((float)ns::Config::Window::view_width/2, (float)ns::Config::Window::view_height/2) - bmp_text->getSize()/2.f);
    // adding the BitmapText to the layer
    this->scene->getLayer("entities")->add(bmp_text);

    // adding debug texts
    // directly using addDebugText to create automatically a DebugText object
    this->addDebugText<int>(&this->frame_counter, "frame counter:", {10, 10});
    this->addDebugText<sf::Vector2f, ns::BaseEntity>(this->player.get(), &ns::BaseEntity::getPosition, "position:", {10, 50}, sf::Color(20, 255, 20));

    // you can change debug text global properties by using DebugTextInterface (will be applied to ALL debug texts created after)
    ns::DebugTextInterface::color = sf::Color::Cyan;
    ns::DebugTextInterface::outline_thickness = 1;
    ns::DebugTextInterface::outline_color = sf::Color::Blue;
    this->addDebugText<sf::Vector2f, ns::ecs::PhysicsComponent>(this->player->physics(), &ns::ecs::PhysicsComponent::getVelocity, "velocity:", {10, 90});

    // by creating manually a DebugText object, changing its properties and adding it to the app; the app will delete automatically
    // the debug texts, so don't worry about memory
    auto* dbg_txt = new ns::DebugText<float, ns::BaseEntity>(this->player.get(), &ns::BaseEntity::getY, "Y position:", {500, 10});
    dbg_txt->setFillColor(sf::Color::Black);
    dbg_txt->setOutlineThickness(1);
    dbg_txt->setOutlineColor(sf::Color::White);
    this->addDebugText(dbg_txt);

    // creating a camera
    this->game_camera = this->createCamera("game_camera", 0, ns::IntRect(0, 0, 1080/2, 720/2));
    // telling the camera to look at the scene
    this->game_camera->lookAt(this->scene);
    // telling the camera to follow our entity
    this->game_camera->follow(*this->player);
    // the camera will have 10 frames delay over the player
    this->game_camera->setFramesDelay(10);
}

void Game::onEvent(sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
            this->getWindow().close();
            break;

        case sf::Event::KeyReleased:
            if(event.key.code == ns::Config::Inputs::getButtonKey("fullscreen"))
                this->toggleFullscreen();
            if (event.key.code == sf::Keyboard::Escape)
                this->getWindow().close();
            break;

        default:
            break;
    }
}

void Game::update() {
    this->frame_counter++;

    // moving the octogons randomly
    for (const auto& drawable: this->scene->getLayer(1)->getDrawables()) {
        std::visit([&](auto&& arg){arg->move((float)(std::rand()%3) - 1.f, (float)(std::rand()%3) - 1.f);}, drawable);
    }

    // updating the player entity
    this->player->update();

    // sorting the shapes layer by the y position
    //this->scene->getLayer(1)->ySort();
}

Game::~Game() = default;

