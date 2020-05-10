/**
* Created by Modar Nasser on 26/04/2020.
**/

#include "Game.hpp"

#include "Sprites.hpp"

Game::Game() :
App("NasNas++ demo", 1080, 720, 1080/2, 720/2)
{

    auto* game_sprites = new Sprites();
    this->player = std::make_shared<ns::BaseEntity>("Player", &game_sprites->player_spr);
    this->player->setPosition({100, 100});

    auto colors = std::vector<sf::Color>{sf::Color::Blue, sf::Color::Red, sf::Color::Green,
                                         sf::Color::Yellow, sf::Color::Cyan, sf::Color::Magenta,
                                         sf::Color::White, sf::Color::Black};

    this->scene = this->createScene(1600, 900);

    this->scene->addLayer(std::make_shared<ns::Layer>("layer0"), 0);
    this->scene->addLayer(std::make_shared<ns::Layer>("layer1"), 1);


    auto rect2 = std::make_shared<sf::RectangleShape>(sf::Vector2f(1600, 900));
    this->scene->getLayer(0)->add(rect2);

    for (int i = 0; i < 100; ++i) {
        auto shape = std::make_shared<sf::CircleShape>(20.0f);
        shape->setPointCount(8);
        shape->setFillColor(colors.at(i%8));
        shape->setOutlineColor(sf::Color::Black);
        shape->setOutlineThickness(1);
        shape->setOrigin(20, 20);
        shape->setPosition((float)(std::rand()%W_WIDTH), (float)(std::rand()%W_HEIGHT));
        this->scene->getLayer(1)->add(shape);
    }
    auto mylayer = std::make_shared<ns::Layer>("mylayer");
    this->scene->addLayer(mylayer, 2);

    this->addDebugText<sf::Vector2f>(&this->player->getVelocity(), "velocity:: ", {10, 10});

    this->scene->getLayer(2)->add(this->player);

    std::function<float(const ns::BaseEntity&)> player_x = &ns::BaseEntity::getX;
    std::cout << player_x(*this->player) << std::endl;

    this->game_camera->lookAt(this->scene);
    this->game_camera->follow(*this->player);
    this->game_camera->setFramesDelay(10);

}

void Game::update() {
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
    else{
        //if(this->player.getVelocity().x > 0)
        //    this->player.getVelocity().x -=  0.2;
        //if(this->player.getVelocity().x < 0)
        //    this->player.getVelocity().x +=  0.2;
//
        //if (this->player.getVelocity().y > 0)
        //    this->player.getVelocity().y -= 0.2;
        //if (this->player.getVelocity().y < 0)
        //    this->player.getVelocity().y += 0.2;
//
    }

    for (const auto& drawable: this->scene->getLayer(1)->getDrawables()) {
        std::visit([&](auto&& arg){arg->move(std::rand()%3 -1, std::rand()%3 -1);}, drawable);
    }
    this->player->update();

    //this->scene->getLayer(0)->ySort();
}

void Game::onEvent(sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
            this->getWindow().close();
            break;

        case sf::Event::KeyPressed:
            switch (event.key.code) {
                default:
                    break;
            }
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

