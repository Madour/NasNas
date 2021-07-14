// Created by Modar Nasser on 11/07/2021.

#include <NasNas/NasNas>

struct RectangleEntity : ns::BaseEntity {
    RectangleEntity(float x, float y, float w, float h) : ns::BaseEntity("rectangle") {
        auto& body = add<ns::ecs::RigidBodyComponent>();
        body.mass = 0.f;
        body.restitution = 0.5f;
        body.friction = 0.5f;

        auto& shape = add<ns::ecs::RectangleShape>(sf::RectangleShape());
        shape.getDrawable().setFillColor(sf::Color::Magenta);
        shape.getDrawable().setSize({w, h});

        get<ns::ecs::TransformComponent>()->setPosition(x, y);

        auto coll = std::make_unique<ns::ecs::RectangleCollider>();
        coll->width = w;
        coll->height = h;

        auto& collider_group = add<ns::ecs::ColliderGroupComponent>(std::move(coll));
    }

    void update() override {
    }
};

struct CircleEntity : ns::BaseEntity {
    CircleEntity() : ns::BaseEntity("circle") {
        auto& body = add<ns::ecs::RigidBodyComponent>();
        body.mass = 2.f;
        body.restitution = 0.5f;
        body.friction = 0.5f;

        auto& shape = add<ns::ecs::CircleShape>(sf::CircleShape(25));
        shape.getDrawable().setFillColor(sf::Color::Yellow);
        shape.getDrawable().setOrigin(25, 25);
        /*if (std::rand()%3 == 0) {
            body.mass = 0.f;
            shape.getDrawable().setFillColor(sf::Color::Magenta);
        }*/

        get<ns::ecs::TransformComponent>()->setPosition(100, 100);

        auto coll = std::make_unique<ns::ecs::CircleCollider>();
        coll->radius = 25;

        auto& collider_group = add<ns::ecs::ColliderGroupComponent>(std::move(coll));
    }
};


struct PlayerEntity : ns::BaseEntity {
    PlayerEntity() : ns::BaseEntity("player") {
        auto& body = add<ns::ecs::RigidBodyComponent>();
        body.mass = 2.f;
        body.restitution = 0.5f;
        body.friction = 0.5f;

        auto& inputs = add<ns::ecs::Inputs>();
        inputs.bind(sf::Keyboard::Up, [&]{body.force += {0, -1.f};});
        inputs.bind(sf::Keyboard::Down, [&]{body.force += {0, 1.f/5.f};});
        inputs.bind(sf::Keyboard::Left, [&]{body.force += {-1.f/5.f, 0};});
        inputs.bind(sf::Keyboard::Right, [&]{body.force += {1.f/5.f, 0};});

        auto& shape = add<ns::ecs::RectangleShape>(sf::RectangleShape());
        shape.getDrawable().setOrigin(0, 0);
        shape.getDrawable().setSize({50, 50});

        auto coll = std::make_unique<ns::ecs::RectangleCollider>();
        coll->width = 50;
        coll->height = 50;
        auto& collider_group = add<ns::ecs::ColliderGroupComponent>(std::move(coll));
    }

    void update() override {
        inputs()->update();
    }
};

class Game : public ns::App {
    PlayerEntity player;
    RectangleEntity ground{0, 550, 1100, 20};
    RectangleEntity wall{5, 20, 20, 720};
    RectangleEntity wall2{1100, 20, 20, 720};
    std::vector<CircleEntity> circles;
public:
    Game() : ns::App("physics", {1280, 720}) {
        auto& scene = createScene("main");
        auto& camera = createCamera("main", 0);

        camera.lookAt(scene);

        circles.reserve(200);
        circles.resize(10);
        scene.getDefaultLayer().add(player);
        scene.getDefaultLayer().add(wall);
        scene.getDefaultLayer().add(wall2);
        scene.getDefaultLayer().add(ground);
        for (auto& circle : circles) {
            circle.get<ns::ecs::TransformComponent>()->setPosition(std::rand()%1280, std::rand()%720);
            scene.getDefaultLayer().add(circle);
        }
        ns::ecs::World::get().step();
        //for (auto& line : ns::ecs::World::get().lines)
            //scene.getDefaultLayer().add(line);

        addDebugText<sf::Vector2f>("pl pos", [&]{return player.getPosition();}, {10, 10});
        addDebugText<sf::Vector2f>("pl vel", [&]{return player.get<ns::ecs::RigidBodyComponent>()->velocity;}, {10, 40});

        // addDebugText<sf::Vector2f>("circle pos", [&]{return circles[0].getPosition();}, {800, 10});
        // addDebugText<sf::Vector2f>("circle vel", [&]{return circles[0].get<ns::ecs::RigidBodyComponent>()->velocity;}, {800, 40});
    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta < 0)
                getCamera("main").zoom(1.05f);
            if (event.mouseWheelScroll.delta > 0)
                getCamera("main").zoom(0.95f);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                circles.emplace_back();
                auto& circle = circles.back();
                circle.get<ns::ecs::TransformComponent>()->setPosition(getMousePosition(getCamera("main")));
                getScene("main").getDefaultLayer().add(circle);
            }
        }
    }

    void update() override {
        player.update();
        auto& cam = getCamera("main");

        auto& tr_player = *player.get<ns::ecs::TransformComponent>();
        auto margin = 0;
        if (tr_player.getPosition().x > cam.getRight() + margin)
            tr_player.setPositionX(cam.getLeft() - margin);
        else if (tr_player.getPosition().x < cam.getLeft() - margin)
            tr_player.setPositionX(cam.getRight() + margin);

        if (tr_player.getPosition().y > cam.getBottom() + margin)
            tr_player.setPositionY(cam.getTop() - margin);

        /*for (auto& circle : circles) {
            auto& tr_circle = *circle.get<ns::ecs::TransformComponent>();

            if (tr_circle.getPosition().x > cam.getRight() + margin)
                tr_circle.setPositionX(cam.getLeft() - margin);
            else if (tr_circle.getPosition().x < cam.getLeft() - margin)
                tr_circle.setPositionX(cam.getRight() + margin);

            if (tr_circle.getPosition().y > cam.getBottom() + margin)
                tr_circle.setPositionY(cam.getTop() - margin);
            else if (tr_circle.getPosition().y < cam.getTop() - margin)
                tr_circle.setPositionY(cam.getBottom() + margin);
        }*/

    }
};


int main() {
    std::srand(std::time(nullptr));

    Game g;
    g.run();

    return 0;
}