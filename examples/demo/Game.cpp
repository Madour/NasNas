/**
* Created by Modar Nasser on 26/04/2020.
**/

#include "Game.hpp"

#include "Player.hpp"
#include "ShaderTransition.hpp"

Game::Game() :
ns::App("NasNas demo", {640, 360}, 2, 60, 60) {
    //------------ Game Config ----------------------------------------------------------
    // mapping keys inputs
    ns::Config::Inputs::setButtonKey("left", sf::Keyboard::Left);
    ns::Config::Inputs::setButtonKey("right", sf::Keyboard::Right);
    ns::Config::Inputs::setButtonKey("up", sf::Keyboard::Up);
    ns::Config::Inputs::setButtonKey("down", sf::Keyboard::Down);
    ns::Config::Inputs::setButtonKey("fullscreen", sf::Keyboard::F);
    // configuring physics constants
    ns::Config::Physics::gravity = 0;
    //-----------------------------------------------------------------------------------

    //------------ Creating Game Objects ------------------------------------------------
    // loading tiled map from file
    this->tiled_map.loadFromFile("assets/test_map.tmx");

    // generating 100 random octogons
    auto colors = std::vector<sf::Color>{
        sf::Color::Blue, sf::Color::Red, sf::Color::Green, sf::Color::Yellow,
        sf::Color::Cyan, sf::Color::Magenta, sf::Color::White
    };
    for (int i = 0; i < 100; ++i) {
        auto shape = std::make_shared<sf::CircleShape>(20.0f);
        shape->setPointCount(8);
        shape->setFillColor(colors.at(i%colors.size()));
        shape->setOutlineColor(sf::Color::Black);
        shape->setOutlineThickness(1);
        shape->setOrigin(20, 20);
        shape->setPosition((float)(std::rand()%2500), (float)(std::rand()%2000));
        this->shapes.push_back(shape);
    }

    // creating Player entity (see class Player for more information)
    this->player = std::make_shared<Player>();
    this->player->transform()->setPosition({100, 100});
    this->entities.push_back(this->player);

    // creating a BitmapFont
    this->font = new ns::BitmapFont(
        ns::Res::getTexture("font.png"),
        {8, 8},
        " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;!?-+=",
        {{"ABCDEFGHIJKMNOPQRSTUVWXYZ?=-", 7}, {"ijlntsofpqrux", 5}},
        6
    );
    // creating a BitmapText using the font created above
    auto bmp_text = std::make_shared<ns::BitmapText>("Press E to toggle Shader \nPress R to run Shader Transition\nPress T to run Circle Transition");
    bmp_text->setFont(this->font);
    bmp_text->setPosition(250, 80);

    this->textbox = std::make_shared<ns::ui::TypedText>("TypedText is useful in RPG games ! It creates a typing animation and can be configured to display text on multiple pages.");
    this->textbox->setFont(this->font);
    this->textbox->setMaxWidth(200);
    this->textbox->setMaxLines(2);
    this->textbox->setTypingDelay(5);
    this->textbox->setPosition(250, 125);

    //-----------------------------------------------------------------------------------

    //------------ Creating a Scene and its Layers --------------------------------------
    this->scene = this->createScene("main");
    this->scene->addLayer("shapes", 0); // create a new Layer
    this->scene->addLayer("entities", 1);
    this->scene->addLayer("texts", 2);
    //-----------------------------------------------------------------------------------

    //------------ Creating a Camera ----------------------------------------------------
    auto game_view = sf::Vector2i(640, 360);
    this->game_camera = this->createCamera("game_camera", 0, {{0, 0}, game_view});
    this->game_camera->lookAt(this->scene);     // telling the Camera to look at the scene
    this->game_camera->follow(*this->player);   // telling the Camera to follow our entity
    this->game_camera->setFramesDelay(2);       // the Camera will have 10 frames delay over the player
    // setting Camera limits
    //this->game_camera->setLimitsRect({{0, 0}, sf::Vector2i(tiled_map.getSize())});
    //-----------------------------------------------------------------------------------

    //------------ Adding Drawables to the Scene  ---------------------------------------
    // adding tiledmap layers to the scene
    this->scene->getDefaultLayer()->add(this->tiled_map.getTileLayer("bg"));
    this->scene->getDefaultLayer()->add(this->tiled_map.getTileLayer("front"));
    this->scene->getDefaultLayer()->add(this->tiled_map.getObjectLayer("objects"));

    // adding shapes
    for (auto& shape : this->shapes) {
        this->scene->getLayer("shapes")->add(shape);
    }

    // adding entities
    this->scene->getLayer("entities")->add(this->player);

    // adding the BitmapText to the layer
    this->scene->getLayer("texts")->add(bmp_text);
    this->scene->getLayer("texts")->add(textbox);
    //-----------------------------------------------------------------------------------

    //------------ Adding DebugTexts to the App -----------------------------------------
    // adding a DebugText by using addDebugText method
    this->addDebugText<int>("frame counter:", &this->frame_counter, {10, 10});
    this->addDebugText<int>("nb of transitions:", [&]{return ns::Transition::list.size();}, {10, 50}, sf::Color::Green);

    // you can change debug text global properties by using DebugTextInterface
    // (will be applied to ALL debug texts created afterwards)
    ns::DebugTextInterface::color = sf::Color::Cyan;
    ns::DebugTextInterface::outline_thickness = 1;
    ns::DebugTextInterface::outline_color = sf::Color::Blue;
    this->addDebugText<sf::Vector2i>("mouse pos:", [&]{return sf::Mouse::getPosition(getWindow());}, {10, 90});

    // add DebugText by creating manually a DebugText object, changing its properties and adding it to the app;
    // the app will delete automatically the debug texts, so don't worry about memory
    auto* dbg_txt = new ns::DebugText<sf::Vector2f>("position:", [&]{return player->getPosition();}, {500, 10});
    dbg_txt->setFillColor(sf::Color::Black);
    dbg_txt->setOutlineThickness(1);
    dbg_txt->setOutlineColor(sf::Color::White);
    this->addDebugText(dbg_txt);
    //-----------------------------------------------------------------------------------

    this->palette_shader = new sf::Shader();
    this->palette_shader->loadFromMemory(
        "uniform sampler2D texture;"
        "uniform float threshold;"
        "void main()"
        "{"
            "vec2 pos = gl_TexCoord[0].xy;"
            "vec4 col = texture2D(texture, pos);"
            "vec4 new_col = col;"
            "if (col.r <= threshold)"
                "new_col = vec4(0.20, 0.35, 0.1, 1.);"
            "else if (col.r <= threshold + 0.25f)"
                "new_col = vec4(0.4, 0.7, 0.3, 1.);"
            "else if (col.r <= threshold + 0.5f)"
                "new_col = vec4(0.6, 0.8, 0.6, 1.);"
            "else if (col.r <= threshold + 0.75f)"
                "new_col = vec4(0.90, 0.99, 0.90, 1.);"
            "else "
                "new_col = vec4(0.90, 0.99, 0.90, 1.);"
            "gl_FragColor = new_col;"
        "}",
        sf::Shader::Fragment
    );
    this->palette_shader->setUniform("threshold", 0.25f);
    this->setShader(palette_shader);
    this->toggleShader();

}

void Game::onEvent(const sf::Event& event) {
    textbox->onEvent(event);
    switch (event.type) {
        case sf::Event::Closed:
            this->getWindow().close();
            break;

        case sf::Event::KeyReleased:
            if(event.key.code == ns::Config::Inputs::getButtonKey("fullscreen"))
                this->toggleFullscreen();
            if (event.key.code == sf::Keyboard::Escape)
                this->getWindow().close();

            if (event.key.code == sf::Keyboard::F1)
                ns::Config::debug = !ns::Config::debug;
            if (event.key.code == sf::Keyboard::F2)
                ns::Config::debug.show_fps = !ns::Config::debug.show_fps;
            if (event.key.code == sf::Keyboard::F3)
                ns::Config::debug.show_text = !ns::Config::debug.show_text;
            if (event.key.code == sf::Keyboard::F4)
                ns::Config::debug.show_bounds = !ns::Config::debug.show_bounds;

            if (event.key.code == sf::Keyboard::E) {
                this->toggleShader();
            }
            if (event.key.code == sf::Keyboard::R) {
                auto* tr = new ShaderOutTransition("threshold");
                tr->start();
                tr->setOnEndCallback([](){
                    auto* next = new ShaderInTransition("threshold");
                    next->start();
                });
            }
            if (event.key.code == sf::Keyboard::T) {
                auto* tr = new ns::transition::CircleClose();
                tr->start();
                tr->setOnEndCallback([](){
                    auto* next = new ns::transition::CircleOpen();
                    next->start();
                });
            }
            break;

        default:
            break;
    }
}

void Game::update() {
    this->frame_counter++;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        game_camera->rotate(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        game_camera->rotate(-1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        game_camera->zoom(1.01f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        game_camera->zoom(0.99f);

    this->textbox->update();
    // moving the octogons randomly
    for (const auto& shape: this->shapes) {
        shape->move((float)(std::rand()%3) - 1.f, (float)(std::rand()%3) - 1.f);
        shape->rotate(1);
    }

    // updating map layers
    this->tiled_map.update();

    // updating the entities
    for (const auto& entity : this->entities)
        entity->update();

    // sorting the shapes layer by the y position
    // this->scene->getLayer("shapes")->ySort();
}

Game::~Game() {
    delete(this->palette_shader);
    delete(this->font);
}
