/**
* Created by Modar Nasser on 26/04/2020.
**/

#include "Game.hpp"

#include "Player.hpp"
#include "Wall.hpp"
#include "ShaderTransition.hpp"

Game::Game() :
ns::App("NasNas++ demo", 1280, 720, 640, 360, 60, 60) {
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
    this->player->setPosition({100, 100});
    this->entities.push_back(this->player);

    // creating Wall entity
    auto wall = std::make_shared<Wall>(200.f, 200.f);
    this->entities.push_back(wall);

    // creating a BitmapFont
    auto bmp_font = std::make_shared<ns::BitmapFont>(
            ns::Res::get().getTexture("font.png"),
            sf::Vector2u(8, 8),
            " ABCDEFGHIJKLMNOPQRSTUVWXYZ",
            std::unordered_map<char, int>({{'I', 7}, {'L', 7}})
    );
    // creating a BitmapText using the font created above
    auto bmp_text = std::make_shared<ns::BitmapText>("PRESS E TO TOGGLE SHADER \nPRESS R TO RUN SHADER TRANSITION\nPRESS T TO RUN CIRCLE TRANSITION");
    bmp_text->setFont(bmp_font);
    bmp_text->setPosition(250, 80);

    textbox = std::make_shared<ns::ui::TypedText>("TYPEDTEXT CAN DYNAMICALLY GENERATE LINE BREAKS AND MULTIPLE PAGES DEPENDING ON ITS MAX WIDTH AND MAX LINES");
    textbox->setFont(bmp_font);
    textbox->setMaxWidth(200);
    textbox->setMaxLines(2);
    textbox->setTypingDelay(5);
    textbox->setPosition(250, 125);
    //-----------------------------------------------------------------------------------

    //------------ Creating a Scene and its Layers --------------------------------------
    this->scene = this->createScene("main");
    this->scene->addLayer("shapes", 0); // creating new Layer using layer name (recommanded)
    this->scene->addLayer(new ns::Layer("entities"), 1);  // creating new Layer using raw pointer
    this->scene->addLayer(std::make_shared<ns::Layer>("texts"), 2);  // creating new Layer using smart pointer
    //-----------------------------------------------------------------------------------

    //------------ Creating a Camera ----------------------------------------------------
    auto camera_view = ns::IntRect(0, 0, ns::Config::Window::view_width, ns::Config::Window::view_height);
    this->game_camera = this->createCamera("game_camera", 0, camera_view);
    this->game_camera->lookAt(this->scene);     // telling the Camera to look at the scene
    this->game_camera->follow(*this->player);   // telling the Camera to follow our entity
    this->game_camera->setFramesDelay(10);      // the Camera will have 10 frames delay over the player
    // setting Camera limits
    this->game_camera->setLimitsRectangle(ns::IntRect(
            {0, 0},
            {(int)(tiled_map.getSize().x*tiled_map.getTileSize().x), (int)(tiled_map.getSize().y*tiled_map.getTileSize().y)}
    ));
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
    this->scene->getLayer("entities")->add(wall);

    // adding the BitmapText to the layer
    this->scene->getLayer("texts")->add(bmp_text);
    this->scene->getLayer("texts")->add(textbox);
    //-----------------------------------------------------------------------------------

    //------------ Adding DebugTexts to the App -----------------------------------------
    // adding a DebugText by using addDebugText method
    this->addDebugText<int>(&this->frame_counter, "frame counter:", {10, 10});
    this->addDebugText<int>([&](){return ns::Transition::list.size();}, "nb of transitions:", {10, 50}, sf::Color::Green);

    // you can change debug text global properties by using DebugTextInterface
    // (will be applied to ALL debug texts created afterwards)
    ns::DebugTextInterface::color = sf::Color::Cyan;
    ns::DebugTextInterface::outline_thickness = 1;
    ns::DebugTextInterface::outline_color = sf::Color::Blue;
    this->addDebugText<sf::Vector2f>([&](){return player->physics()->getVelocity();}, "velocity:", {10, 90});

    // add DebugText by creating manually a DebugText object, changing its properties and adding it to the app;
    // the app will delete automatically the debug texts, so don't worry about memory
    auto* dbg_txt = new ns::DebugText<sf::Vector2f, ns::BaseEntity>(this->player.get(), &ns::BaseEntity::getPosition, "position:", {500, 10});
    dbg_txt->setFillColor(sf::Color::Black);
    dbg_txt->setOutlineThickness(1);
    dbg_txt->setOutlineColor(sf::Color::White);
    this->addDebugText(dbg_txt);
    //-----------------------------------------------------------------------------------

    // setting a shader for fun
    black_white_shader = new sf::Shader();
    black_white_shader->loadFromMemory(
        "uniform sampler2D texture;"
        "void main()"
        "{"
            "vec2 pos = gl_TexCoord[0].xy;"
            "vec4 col = texture2D(texture, pos);"
            "float l = col.r*0.33f + col.g*0.33f + col.b*0.33f;"
            "vec4 new_col = vec4(1.0-col.r, 1.0-col.g, 1.0-col.b, col.a);"
            "if (l < 0.25f)"
                "new_col = vec4(0.15, 0.15, 0.15, 1.);"
            "else if (l < 0.5f)"
                "new_col = vec4(0.4, 0.4, 0.4, 1.);"
            "else if (l < 0.75f)"
                "new_col = vec4(0.7, 0.7, 0.7, 1.);"
            "else if (l <= 1.f)"
                "new_col = vec4(0.99, 0.99, 0.99, 1.);"
            "gl_FragColor = new_col;"
        "}",
        sf::Shader::Fragment
    );
    this->game_camera->setShader(black_white_shader);
    this->game_camera->toggleShader();

    palette_shader = new sf::Shader();
    palette_shader->loadFromMemory(
        "uniform sampler2D texture;"
        "uniform float treshold;"
        "void main()"
        "{"
            "vec2 pos = gl_TexCoord[0].xy;"
            "vec4 col = texture2D(texture, pos);"
            "vec4 new_col = col;"
            "if (col.r <= treshold)"
                "new_col = vec4(0.20, 0.35, 0.1, 1.);"
            "else if (col.r <= treshold + 0.25f)"
                "new_col = vec4(0.4, 0.7, 0.3, 1.);"
            "else if (col.r <= treshold + 0.5f)"
                "new_col = vec4(0.6, 0.8, 0.6, 1.);"
            "else if (col.r <= treshold + 0.75f)"
                "new_col = vec4(0.90, 0.99, 0.90, 1.);"
            "gl_FragColor = new_col;"
        "}",
        sf::Shader::Fragment
    );
    palette_shader->setUniform("treshold", 0.25f);
    this->setShader(palette_shader);
    toggleShader();
}

void Game::onEvent(sf::Event event) {
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

            if (event.key.code == sf::Keyboard::E) {
                this->game_camera->toggleShader();
                this->toggleShader();
            }
            if (event.key.code == sf::Keyboard::R) {
                auto* tr = new ShaderOutTransition("treshold");
                tr->start();
                tr->setOnEndCallback([](){
                    auto* next = new ShaderInTransition("treshold");
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
    textbox->update();
    // moving the octogons randomly
    for (const auto& shape: this->shapes) {
        shape->move((float)(std::rand()%3) - 1.f, (float)(std::rand()%3) - 1.f);
        shape->rotate(1);
    }

    // collision check
    if (this->player->collider()->getCollision().collide(this->entities[1]->collider()->getCollision()))
        ns_LOG("Collision between player and wall");

    // updating map layers
    this->tiled_map.getTileLayer("bg")->update();
    this->tiled_map.getTileLayer("front")->update();

    // updating the entities
    for (const auto& entity : this->entities)
        entity->update();

    // sorting the shapes layer by the y position
    // this->scene->getLayer("shapes")->ySort();
}

Game::~Game() {
    delete(black_white_shader);
    delete(palette_shader);
};
