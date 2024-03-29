/**
* Created by Modar Nasser on 26/04/2020.
**/

#include <cmath>
#include "Game.hpp"

Game::Game() : ns::App("NasNas sandbox", {640, 360}, 2, 60, 60) {
    //------------ Game Objects creation ------------------------------------------------
    // load tiled map from file
    this->tiled_map.loadFromFile("assets/test_map.tmx");

    // generate 100 random octogons
    auto colors = std::vector<sf::Color>{
        sf::Color::Blue, sf::Color::Red, sf::Color::Green, sf::Color::Yellow,
        sf::Color::Cyan, sf::Color::Magenta, sf::Color::White
    };
    for (int i = 0; i < 100; ++i) {
        auto shape = sf::CircleShape(20.0f);
        shape.setPointCount(8);
        shape.setFillColor(colors.at(i%colors.size()));
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        shape.setOrigin(20, 20);
        shape.setPosition((float)(std::rand()%2500), (float)(std::rand()%2000));
        this->shapes.push_back(shape);
    }

    // create Player entity (see class Player for more information)
    this->player.get<ns::ecs::Transform>().setPosition({100, 100});

    // create a BitmapFont
    font.loadFromTexture(ns::Res::getTexture("font.png"), {8, 8}, 5);
    font.setCharacters(L"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklm"
                       L"nopqrstuvwxyz0123456789.,:;!?-+=☺☻♥♦♣♠");
    font.setCharactersAdvance({{L"fijlt.,:;", 3},
                               {L"Tabcdeghknopqrsuvwxyz?+-=", 4},
                               {L"_0123456789ABCDEFGHIJKLMNOPQRSUVXYZmw", 6},
                               {L"W", 7}});
    // create a BitmapText using the font created above
    auto* bmp_text = new ns::BitmapText();
    bmp_text->setString("Press E to toggle Shader\nPress R to run Shader Transition\nPress T to run Circle Transition");
    bmp_text->setFont(this->font);
    bmp_text->setLineSpacing(1.2f);
    bmp_text->setPosition(250, 65);

    // setup the particle system and emmit 500 particles
    this->particle_system.setTexture(ns::Res::getTexture("tileset.png"));
    this->particle_system.setEmitRate(30.f);
    this->particle_system.emit({224, 32, 16, 16}, 300, true);

    //-----------------------------------------------------------------------------------

    //------------ Scene and Layers creation --------------------------------------------
    auto& scene = this->createScene("main");            // create a scene
    scene.createLayers("shapes", "entities", "texts");  // create 3 layers
    //-----------------------------------------------------------------------------------

    //------------ Camera creation ------------------------------------------------------
    auto game_view = sf::Vector2i(640, 360);
    auto& game_camera = this->createCamera("main", 0, {{0, 0}, game_view});
    game_camera.lookAt(scene);     // tell the Camera to look at the scene
    game_camera.follow(this->player.get<ns::ecs::Transform>());   // tell the Camera to follow the player entity
    game_camera.setFramesDelay(15);       // the Camera will have 7 frames delay over the player
    game_camera.setLimitsRect({{0, 0}, sf::Vector2i(this->tiled_map.getSize())});
    this->tiled_map.setCamera(game_camera);
    //-----------------------------------------------------------------------------------

    //------------ Add Drawables to the Scene  ------------------------------------------
    // add tiledmap layers to the scene one by one
    scene.getDefaultLayer().add(this->tiled_map.getTileLayer("bg"));
    // or add the whole group at once
    scene.getDefaultLayer().add(this->tiled_map.getGroupLayer("FrontGroup"));

    // add shapes
    for (auto& shape : this->shapes) {
        scene.getLayer("shapes").add(shape);
    }

    // add entities
    scene.getLayer("entities").add(this->player);

    // add the BitmapText to the layer
    scene.getLayer("texts").add(bmp_text);

    // add the particle system
    scene.getLayer("texts").add(this->particle_system);
    //-----------------------------------------------------------------------------------

    //------------ Add DebugTexts to the App -----------------------------------------
    // add a DebugText by using addDebugText method
    this->addDebugText<int>("frame counter:", &this->frame_counter, {10, 10}, sf::Color::Yellow);
    this->addDebugText<sf::Vector2f>("player pos:", [&]{return this->player.getPosition();}, {10, 50});

    // you can change debug text global properties by using DebugTextInterface
    // (will be applied to ALL debug texts created afterwards)
    ns::DebugTextInterface::color = sf::Color::Cyan;
    ns::DebugTextInterface::outline_thickness = 1;
    ns::DebugTextInterface::outline_color = sf::Color::Blue;
    this->addDebugText<sf::Vector2f>("mouse pos:", [&]{return getMousePosition(getCamera("main"));}, {10, 90});
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
    ns::App::onEvent(event);

    switch (event.type) {
        case sf::Event::Closed:
            this->getWindow().close();
            break;

        case sf::Event::KeyReleased:
            if(event.key.code == ns::Inputs::getButton("fullscreen")) {
                this->toggleFullscreen();
            }
            if (event.key.code == sf::Keyboard::E) {
                this->toggleShader();
            }
            if (event.key.code == sf::Keyboard::R) {
                startTransition<ShaderOutTransition>("threshold").onEnd([&]() {
                    startTransition<ShaderInTransition>("threshold");
                });
            }
            if (event.key.code == sf::Keyboard::T) {
                startTransition<ns::transition::CircleClose>().onEnd([&]() {
                    startTransition<ns::transition::CircleOpen>();
                });
            }
            break;

        default:
            break;
    }
}

void Game::update() {
    this->frame_counter++;

    // run the default input systems (call inputs components callbacks when needed)
    ns::Ecs.run(ns::ecs::inputs_system);
    // run the default physics systems (adds force to velocity and apply friction)
    ns::Ecs.run(ns::ecs::physics_system);
    // run a custom system that updates transformable components according to physics velocity
    ns::Ecs.run<ns::ecs::Transform, ns::ecs::Physics>([](auto& transform, auto& physics) {
        transform.move(physics.linear_velocity);
    });
    // run the default sprite component to update sprite animation
    ns::Ecs.run(ns::ecs::sprite_system);

    // move the shapes randomly
    for (auto& shape : this->shapes) {
        shape.move((float)(std::rand()%3) - 1.f, (float)(std::rand()%3) - 1.f);
        shape.rotate(1);
    }

    // update the player
    this->player.update();

    // update tiled map
    this->tiled_map.update();

    // sort shapes layer by the y position
    this->getScene("main").getLayer("shapes").ySort();

    // update particles
    this->particle_system.setPosition(getMousePosition(getCamera("main")));
    this->particle_system.update();
}

Game::~Game() {
    delete(this->palette_shader);
}
