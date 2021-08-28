/**
* Created by Modar Nasser on 06/02/2020.
**/

#include <algorithm>
#include <exception>
#include <queue>
#include <NasNas/Core.hpp>
#include <NasNas/Ecs.hpp>
#include "NasNas/ecs/components/InputsComponent.hpp"
#include "NasNas/ecs/new/Registry.hpp"

/**
 * This example shows how to create a custom component and how
 * to add it to an Entity
 */
struct HpComponent {
    // component data
    int hp;
    int max_hp;

    // custom component method
    void restore(int amount) {
        hp = std::min(hp+amount, max_hp);
    }

    // custom component method
    void damage(int amount) {
        hp = std::max(0, hp-amount);
    }
};

class MyEntity : public ns::BaseEntity, public sf::Drawable {
public:
    MyEntity() {
        add<sf::Transformable>().setPosition(540, 300);

        // add the custom component to MyEntity
        add<HpComponent>(500, 500);

        // add a RectangleShape component to represent the HP bar
        sf::RectangleShape hp_bar{{0, 20}};
        hp_bar.setFillColor(sf::Color::Red);
        hp_bar.setOrigin(250, 10);
        add<ns::ecs::RectangleShape>(hp_bar);
    }

    void update() {
        // update custom component
        get<HpComponent>().restore(1);
        get<ns::ecs::RectangleShape>().getDrawable().setSize({static_cast<float>(get<HpComponent>().hp), 20.f});
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= get<sf::Transformable>().getTransform();
        target.draw(get<ns::ecs::RectangleShape>().getDrawable(), states);
    }
};

class Game : public ns::App {
public:
    MyEntity* entity;

    Game() : ns::App("Custom components", {1080, 720}) {
        // create a scene and a camera
        auto& scene = this->createScene("main");
        auto& camera = this->createCamera("main", 0);
        camera.lookAt(scene);

        auto ent = ns::Ecs.create();
        auto& inputs = ns::Ecs.attach<ns::ecs::InputsComponent>(ent);
        inputs.onPress(sf::Keyboard::Q, [ent](){std::cout << ent << " : Q pressed\n"; });
        inputs.enable();

        // create MyEntity and add it to the scene
        this->entity = new MyEntity();
        scene.getDefaultLayer().add(this->entity);
    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::KeyPressed) {
            // when space bar is pressed, call damage method of HpComponent
            if (event.key.code == sf::Keyboard::Space) {
                this->entity->get<HpComponent>().damage(50);
            }
        }
    }

    void update() override {
        this->entity->update();
        ns::Ecs.run<ns::ecs::InputsComponent>([](auto& input) {input.update();});
    }
};

int main() {

    Game g;
    g.run();

    return 0;
}
