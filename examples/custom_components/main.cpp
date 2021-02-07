/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas.h>

/**
 * This example shows how to create a custom component and how
 * to add it to an Entity
 */
struct HpComponent : ns::ecs::Component<HpComponent> {
    // component data
    int hp;
    int max_hp;

    // needs a constructor because of virtual method update
    explicit HpComponent(int max_health) :
    hp(max_health),
    max_hp(max_health)
    {}

    // custom component method
    void damage(int amount) {
        hp = std::max(0, hp-amount);
    }

    // the update method inherited from base class
    void update() override {
        hp = std::min(max_hp, hp+1);
    }

};

class MyEntity : public ns::BaseEntity {
public:
    MyEntity() : ns::BaseEntity("MyEntity") {
        transform()->setPosition(540, 300);

        // add the custom component to MyEntity
        add<HpComponent>(500);

        // add a RectangleShape component to represent the HP bar
        sf::RectangleShape hp_bar{{0, 20}};
        hp_bar.setFillColor(sf::Color::Red);
        hp_bar.setOrigin(250, 10);
        add<ns::ecs::RectangleShape>(hp_bar);

    }

    void update() override {
        // update custom component
        get<HpComponent>()->update();
        get<ns::ecs::RectangleShape>()->getDrawable().setSize({static_cast<float>(get<HpComponent>()->hp), 20.f});
    }
};

class Game : public ns::App {
public:
    MyEntity* entity;

    Game() : ns::App("Custom components", {1080, 720}) {

        // create a scene and a camera
        auto* scene = this->createScene("main");
        auto* camera = this->createCamera("main", 0);
        camera->lookAt(scene);

        // create MyEntity and add it to the scene
        this->entity = new MyEntity();
        scene->getDefaultLayer()->add(this->entity);

    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::KeyPressed) {
            // when space bar is pressed, call damage method of HpComponent
            if (event.key.code == sf::Keyboard::Space) {
                this->entity->get<HpComponent>()->damage(50);
            }
        }
    }

    void update() override {
        this->entity->update();
    }
};

int main() {

    Game g;
    g.run();

    return 0;
}
