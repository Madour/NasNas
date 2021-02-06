/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas.h>

struct HpComponent : ns::ecs::BaseComponent {
    int hp;
    int max_hp;

    HpComponent(ns::ecs::ComponentGroup* owner, int health, int max_health) :
    ns::ecs::BaseComponent(owner), hp(health), max_hp(max_health)
    {}

    void damage(int amount) {
        hp = std::max(0, hp-amount);
    }

    void update() override {}

    static unsigned long uid;
    static auto getId() -> unsigned long;
};

unsigned long HpComponent::uid = ns::ecs::BaseComponent::getNextId();
auto HpComponent::getId() -> unsigned long {
    return uid;
}

struct MyEntity : ns::BaseEntity {
    MyEntity() : ns::BaseEntity("MyEntity") {
        add<HpComponent>(50, 50);

        sf::RectangleShape hp_bar{{500, 20}};
        hp_bar.setFillColor(sf::Color::Red);
        hp_bar.setOrigin(250, 10);
        add<ns::ecs::RectangleShape>(hp_bar);

        transform()->setPosition(500, 300);

    }

    void update() override {
        ns::BaseEntity::update();
        get<ns::ecs::RectangleShape>()->getDrawable().setSize({get<HpComponent>()->hp*10.f, 20.f});
    }
};

class Game : public ns::App {
public:
    MyEntity* entity;

    Game() : ns::App("Custom components", {1080, 720}) {

        // create a scene and a camera
        auto* scene = createScene("main");
        auto* camera = createCamera("left", 0);
        camera->lookAt(scene);

        entity = new MyEntity();
        scene->getDefaultLayer()->add(entity);

    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Space) {
                entity->get<HpComponent>()->damage(1);
            }
        }
    }

    void update() override {
        entity->update();
    }
};

int main() {

    Game g;
    g.run();

    return 0;
}
