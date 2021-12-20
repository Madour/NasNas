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
    m_tiled_map.getGroupLayer("front").scale(2.f, 2.f);
    m_tiled_map.getGroupLayer("front").setOrigin(450, 35);
    m_tiled_map.getGroupLayer("sky").getImageLayer("sky").scale(2.f, 2.f);
    m_tiled_map.getGroupLayer("sky").getImageLayer("clouds").scale(2.f, 2.f);

    // create Player entity (see class Player for more information)
    m_player.get<ns::ecs::Transform>().setPosition(100, 250);

    // GUI creation
    m_btn_drawable.setRadius(30);
    m_btn_drawable.setOrigin(30, 30);
    m_btn_drawable.setFillColor({255, 255, 255, 150});

    m_btn_drawable_focused = m_btn_drawable;
    m_btn_drawable_focused.setFillColor({255, 255, 255, 255});

    auto btn_style = ns::ui::Button::Style();
    btn_style.padding.left = 24;
    btn_style.drawable = &m_btn_drawable;
    btn_style.drawable_focused = &m_btn_drawable_focused;
    btn_style.region = new ns::ui::CircleRegion(30);

    auto btn_text = sf::Text("", ns::Arial::getFont());
    btn_text.setCharacterSize(20);

    auto& btn_left = m_gui.addWidget<ns::ui::Button>();
    btn_left.style = btn_style;
    btn_left.text = btn_text;
    btn_left.text.setString("<");
    btn_left.setTextAlign(ns::ui::TextAlign::Left);
    btn_left.setPosition(50, 255);
    btn_left.setCallback(ns::ui::MouseCallback::onFocus, [&](auto* w) { m_player.movement = -1; });
    btn_left.setCallback(ns::ui::MouseCallback::onUnfocus, [&](auto* w) { m_player.movement = 0; });

    auto& btn_right = m_gui.addWidget<ns::ui::Button>();
    btn_right.style = btn_style;
    btn_right.text = btn_text;
    btn_right.text.setString(">");
    btn_right.setTextAlign(ns::ui::TextAlign::Left);
    btn_right.setPosition(110, 255);
    btn_right.setCallback(ns::ui::MouseCallback::onFocus, [&](auto* w) { m_player.movement = 1; });
    btn_right.setCallback(ns::ui::MouseCallback::onUnfocus, [&](auto* w) { m_player.movement = 0; });

    auto& btn_jump = m_gui.addWidget<ns::ui::Button>();
    btn_jump.style = btn_style;
    btn_jump.text = btn_text;
    btn_jump.text.setString("J");
    btn_jump.setTextAlign(ns::ui::TextAlign::Left);
    btn_jump.setPosition(550, 255);
    btn_jump.setCallback(ns::ui::ClickCallback::onTouchBegan, [&](auto* w) { m_player.jump(); });
    //-----------------------------------------------------------------------------------

    //------------ Scene and Layers creation --------------------------------------------
    auto& scene = this->createScene("main");
    scene.createLayers("map_bg", "entities", "map_front");

    auto& gui_scene = this->createScene("gui");
    //-----------------------------------------------------------------------------------


    //------------ Camera creation ------------------------------------------------------
    auto game_view = sf::Vector2i(ns::Settings::getConfig().resolution);
    auto& game_camera = this->createCamera("main", 0, {{0, 0}, game_view});
    game_camera.lookAt(scene);                  // tell the Camera to look at the scene
    game_camera.follow(m_camera_anchor);        // tell the Camera to follow the anchor
    game_camera.setFramesDelay(15);             // the Camera will have 7 frames delay over the player
    game_camera.setLimitsRect({{0, 0}, sf::Vector2i(m_tiled_map.getSize())});
    m_tiled_map.setCamera(game_camera);

    auto& gui_camera = this->createCamera("gui", 0, {{0, 0}, game_view});
    gui_camera.lookAt(gui_scene);
    m_gui.setCamera(gui_camera);
    m_gui.setMaxFingersCount(2);
    //-----------------------------------------------------------------------------------

    //------------ Add Drawables to the Scene  ------------------------------------------
    scene.getLayer("map_bg").add(m_tiled_map.getGroupLayer("sky"));
    scene.getLayer("map_bg").add(m_tiled_map.getGroupLayer("bg"));
    scene.getLayer("map_bg").add(m_tiled_map.getTileLayer("platforms"));
    scene.getLayer("map_front").add(m_tiled_map.getTileLayer("props"));

    scene.getLayer("entities").add(m_player);

    scene.getLayer("map_front").add(m_tiled_map.getGroupLayer("front"));

    gui_scene.getDefaultLayer().add(m_gui);
    //-----------------------------------------------------------------------------------

    //------------ Add DebugTexts to the App -----------------------------------------
    this->addDebugText<int>("frame counter:", &m_frame_counter, {10, 10});
    //-----------------------------------------------------------------------------------
}

void Game::onEvent(const sf::Event& event) {
    ns::App::onEvent(event);
    m_gui.onEvent(event);
}

void Game::update() {
    m_frame_counter++;

    // run the default physics systems (adds force to velocity and apply friction)
    ns::Ecs.run(ns::ecs::physics_system);
    // run a custom system that apply gravity to all physics components
    ns::Ecs.run<ns::ecs::Physics>([&](auto& physics) {
        physics.applyForce(GRAVITY / float(ns::Settings::getConfig().update_rate));
    });
    // run a custom system that updates transformable components according to physics velocity
    ns::Ecs.run<ns::ecs::Transform, ns::ecs::Physics>([](auto& transform, auto& physics) {
        transform.move(physics.linear_velocity);
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
                    ns::Ecs.get<ns::ecs::Physics>(ent1).linear_velocity.x = 0;
                    float sign = (bounds1.left < bounds2.left ? -1.f : 1.f);
                    tr1.move(sign * intersect.width, 0);
                }
                // Y axis collision
                else {
                    ns::Ecs.get<ns::ecs::Physics>(ent1).linear_velocity.y = 0;
                    float sign = (bounds1.top < bounds2.top ? -1.f : 1.f);
                    tr1.move(0, sign * intersect.height);
                }
            }
            // resolve second collider
            if (coll2.dynamic) {
                // X axis collision
                if (intersect.width < intersect.height) {
                    ns::Ecs.get<ns::ecs::Physics>(ent2).linear_velocity.x = 0;
                    float sign = (bounds2.left < bounds1.left ? -1.f : 1.f);
                    tr2.move(sign * intersect.width, 0);
                }
                // Y axis collision
                else {
                    ns::Ecs.get<ns::ecs::Physics>(ent2).linear_velocity.y = 0;
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
            m_player.get<ns::ecs::Physics>().linear_velocity * 5.f +
            sf::Vector2f(0, -40.f)
    );

    // run the default sprite component to update sprite animation
    ns::Ecs.run(ns::ecs::sprite_system);

    // update tiled map
    m_tiled_map.update();
}
