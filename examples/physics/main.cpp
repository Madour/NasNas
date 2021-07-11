// Created by Modar Nasser on 11/07/2021.

#include <NasNas/NasNas>

struct CircleEntity : ns::BaseEntity {
    CircleEntity() : ns::BaseEntity("circle") {
        auto& body = add<ns::ecs::RigidBodyComponent>();
        body.mass = 2.f;
        body.restitution = 0.5f;
        body.friction = 0.5f;

        auto& shape = add<ns::ecs::CircleShape>(sf::CircleShape(25));
        shape.getDrawable().setFillColor(sf::Color::Yellow);
        shape.getDrawable().setOrigin(25, 25);
        if (std::rand()%3 == 0) {
            body.mass = 0.f;
            shape.getDrawable().setFillColor(sf::Color::Magenta);
        }

        get<ns::ecs::TransformComponent>()->setPosition(100, 100);

        auto& collider_group = add<ns::ecs::ColliderGroupComponent>(std::make_unique<ns::ecs::CircleCollider>());
        collider_group.collider().radius = 25;
    }

    void update() override {
    }
};


struct PlayerEntity : ns::BaseEntity {
    PlayerEntity() : ns::BaseEntity("player") {
        auto& body = add<ns::ecs::RigidBodyComponent>();
        body.mass = 2.f;
        body.restitution = 0.5f;
        body.friction = 0.5f;

        auto& inputs = add<ns::ecs::Inputs>();
        inputs.bind(sf::Keyboard::Up, [&]{body.force += {0, -0.1f};});
        inputs.bind(sf::Keyboard::Down, [&]{body.force += {0, 0.1f};});
        inputs.bind(sf::Keyboard::Left, [&]{body.force += {-0.1f, 0};});
        inputs.bind(sf::Keyboard::Right, [&]{body.force += {0.1f, 0};});

        auto& shape = add<ns::ecs::CircleShape>(sf::CircleShape(25));
        shape.getDrawable().setOrigin(25, 25);

        auto& collider_group = add<ns::ecs::ColliderGroupComponent>(std::make_unique<ns::ecs::CircleCollider>());
        collider_group.collider().radius = 25;
    }

    void update() override {
        inputs()->update();
    }
};

class Game : public ns::App {
    PlayerEntity player;
    std::vector<CircleEntity> circles;
public:
    Game() : ns::App("physics", {1280, 720}) {
        auto& scene = createScene("main");
        auto& camera = createCamera("main", 0);

        camera.lookAt(scene);

        circles.resize(1);
        scene.getDefaultLayer().add(player);
        for (auto& circle : circles) {
            circle.get<ns::ecs::TransformComponent>()->setPosition(std::rand()%1280, std::rand()%720);
            scene.getDefaultLayer().add(circle);
        }

        addDebugText<sf::Vector2f>("pl pos", [&]{return player.getPosition();}, {10, 10});
        addDebugText<sf::Vector2f>("pl vel", [&]{return player.get<ns::ecs::RigidBodyComponent>()->velocity;}, {10, 40});

        addDebugText<sf::Vector2f>("circle pos", [&]{return circles[0].getPosition();}, {800, 10});
        addDebugText<sf::Vector2f>("circle vel", [&]{return circles[0].get<ns::ecs::RigidBodyComponent>()->velocity;}, {800, 40});
    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta < 0)
                getCamera("main").zoom(1.05f);
            if (event.mouseWheelScroll.delta > 0)
                getCamera("main").zoom(0.95f);
        }
    }

    void update() override {
        player.update();
        auto& cam = getCamera("main");

        auto& tr_player = *player.get<ns::ecs::TransformComponent>();

        if (tr_player.getPosition().x > cam.getRight() + 50)
            tr_player.setPositionX(cam.getLeft() - 50);
        else if (tr_player.getPosition().x < cam.getLeft() - 50)
            tr_player.setPositionX(cam.getRight() + 50);

        if (tr_player.getPosition().y > cam.getBottom() + 50)
            tr_player.setPositionY(cam.getTop() - 50);
        else if (tr_player.getPosition().y < cam.getTop() - 50)
            tr_player.setPositionY(cam.getBottom() + 50);

        for (auto& circle : circles) {
            auto& tr_circle = *circle.get<ns::ecs::TransformComponent>();

            if (tr_circle.getPosition().x > cam.getRight() + 50)
                tr_circle.setPositionX(cam.getLeft() - 50);
            else if (tr_circle.getPosition().x < cam.getLeft() - 50)
                tr_circle.setPositionX(cam.getRight() + 50);

            if (tr_circle.getPosition().y > cam.getBottom() + 50)
                tr_circle.setPositionY(cam.getTop() - 50);
            else if (tr_circle.getPosition().y < cam.getTop() - 50)
                tr_circle.setPositionY(cam.getBottom() + 50);
        }

    }
};


int main() {
    std::srand(std::time(nullptr));

    Game g;
    g.run();

    return 0;
}