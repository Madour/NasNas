/**
* Created by Modar Nasser on 26/04/2020.
**/

#include "Game.hpp"

const sf::Vector2f GRAVITY{0, 9.8f};

Game::Game() {
    //------------ Game Objects creation ------------------------------------------------
    // load tiled map from file
    m_tiled_map.loadFromFile("assets/platformer.tmx");
    for (auto& rect : m_tiled_map.getObjectLayer("collisions").allRectangles()) {
        auto ent = ns::Ecs.create();
        auto& transform = ns::Ecs.attach<ns::ecs::Transform>(ent);
        auto& collider = ns::Ecs.attach<ns::ecs::AABBCollider>(ent);
        transform.setPosition(rect.x, rect.y);
        collider.size = {rect.width, rect.height};
        collider.position = {rect.width/2.f, rect.height/2.f};
    }
    m_tiled_map.getGroupLayer("front").getTileLayer("front2").scale(1.4f, 1.4f);
    m_tiled_map.getGroupLayer("front").getTileLayer("front2").setOrigin(200, 0);

    // create Player entity (see class Player for more information)
    m_player.get<ns::ecs::Transform>().setPosition(100, 250);
    //-----------------------------------------------------------------------------------

    //------------ Scene and Layers creation --------------------------------------------
    auto& scene = this->createScene("main");
    scene.addLayer("map_bg", 0);
    scene.addLayer("entities", 1);
    scene.addLayer("map_front", 2);
    //-----------------------------------------------------------------------------------

    //------------ Camera creation ------------------------------------------------------
    auto game_view = sf::Vector2i(ns::Settings::getConfig().resolution);
    auto& game_camera = this->createCamera("main", 0, {{0, 0}, game_view});
    game_camera.lookAt(scene);                  // tell the Camera to look at the scene
    game_camera.follow(m_camera_anchor);    // tell the Camera to follow the anchor
    game_camera.setFramesDelay(15);             // the Camera will have 7 frames delay over the player
    game_camera.setLimitsRect({{0, 0}, sf::Vector2i(m_tiled_map.getSize())});
    m_tiled_map.setCamera(game_camera);
    //-----------------------------------------------------------------------------------

    //------------ Add Drawables to the Scene  ------------------------------------------
    scene.getLayer("map_bg").add(m_tiled_map.getTileLayer("sky"));
    scene.getLayer("map_bg").add(m_tiled_map.getGroupLayer("bg"));
    scene.getLayer("map_bg").add(m_tiled_map.getTileLayer("mid"));
    scene.getLayer("map_front").add(m_tiled_map.getGroupLayer("front"));

    scene.getLayer("entities").add(m_player);
    //-----------------------------------------------------------------------------------

    //------------ Add DebugTexts to the App -----------------------------------------
    this->addDebugText<int>("frame counter:", &m_frame_counter, {10, 10});
    //-----------------------------------------------------------------------------------
}

void Game::onEvent(const sf::Event& event) {
    ns::App::onEvent(event);

    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::F1) {
                if (ns::Settings::debug_mode)
                    getScene("main").getLayer("entities").add(m_tiled_map.getObjectLayer("collisions"));
                else
                    getScene("main").getLayer("entities").remove(m_tiled_map.getObjectLayer("collisions"));
            }
            break;

        case sf::Event::KeyReleased:
            if (event.key.code == ns::Inputs::getButton("fullscreen"))
                this->toggleFullscreen();
            else if (event.key.code == sf::Keyboard::R)
                m_player.get<ns::ecs::Transform>().setPosition(100, 250);
            break;

        default:
            break;
    }
}

void Game::update() {
    m_frame_counter++;

    // run the default input systems (call inputs components callbacks when needed)
    ns::Ecs.run(ns::ecs::inputs_system);
    // run the default physics systems (adds force to velocity and apply friction)
    ns::Ecs.run(ns::ecs::physics_system);
    // run a custom system that apply gravity to all physics components
    ns::Ecs.run<ns::ecs::Physics>([&](auto& physics) {
        physics.applyForce(GRAVITY / float(ns::Settings::getConfig().update_rate));
    });
    // run a custom system that updates transformable components according to physics velocity
    ns::Ecs.run<ns::ecs::Transform, ns::ecs::Physics>([](auto& transform, auto& physics) {
        transform.move(physics.getVelocity());
    });

    // resolve collisions using Ecs view to get entities with given components
    auto colls_view = ns::Ecs.view<ns::ecs::AABBCollider, ns::ecs::Transform>();
    colls_view.for_each_pair([&](auto ent1, auto ent2) {
        auto& coll1 = colls_view.get<ns::ecs::AABBCollider>(ent1);
        auto& coll2 = colls_view.get<ns::ecs::AABBCollider>(ent2);

        // no need to solve collision for 2 static colliders
        if (!coll1.dynamic && !coll2.dynamic)
            return;

        auto& tr1 = colls_view.get<ns::ecs::Transform>(ent1);
        auto& tr2 = colls_view.get<ns::ecs::Transform>(ent2);

        auto bounds1 = tr1.getTransform().transformRect(coll1.getBounds());
        auto bounds2 = tr2.getTransform().transformRect(coll2.getBounds());

        sf::FloatRect intersect;
        if (bounds1.intersects(bounds2, intersect)) {
            // resolve first collider
            if (coll1.dynamic) {
                // X axis collision
                if (intersect.width < intersect.height) {
                    ns::Ecs.get<ns::ecs::Physics>(ent1).setVelocityX(0);
                    float sign = (bounds1.left < bounds2.left ? -1.f : 1.f);
                    tr1.move(sign * intersect.width, 0);
                }
                // Y axis collision
                else {
                    ns::Ecs.get<ns::ecs::Physics>(ent1).setVelocityY(0);
                    float sign = (bounds1.top < bounds2.top ? -1.f : 1.f);
                    tr1.move(0, sign * intersect.height);
                }
            }
            // resolve second collider
            if (coll2.dynamic) {
                // X axis collision
                if (intersect.width < intersect.height) {
                    ns::Ecs.get<ns::ecs::Physics>(ent2).setVelocityX(0);
                    float sign = (bounds2.left < bounds1.left ? -1.f : 1.f);
                    tr2.move(sign * intersect.width, 0);
                }
                // Y axis collision
                else {
                    ns::Ecs.get<ns::ecs::Physics>(ent2).setVelocityY(0);
                    float sign = (bounds2.top < bounds1.top ? -1.f : 1.f);
                    tr2.move(0, sign * intersect.height);
                }
            }
        }
    });

    // update the player
    m_player.update();

    m_camera_anchor.setPosition(
            m_player.get<ns::ecs::Transform>().getPosition() +
            m_player.get<ns::ecs::Physics>().getVelocity() * 5.f +
            sf::Vector2f(0, -40.f)
    );

    // run the default sprite component to update sprite animation
    ns::Ecs.run(ns::ecs::sprite_system);

    // update tiled map
    m_tiled_map.update();
}
