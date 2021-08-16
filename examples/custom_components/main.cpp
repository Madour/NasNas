/**
* Created by Modar Nasser on 06/02/2020.
**/

#include <algorithm>
#include <exception>
#include <queue>
#include <NasNas/Core.hpp>
#include <NasNas/Ecs.hpp>

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
        auto& scene = this->createScene("main");
        auto& camera = this->createCamera("main", 0);
        camera.lookAt(scene);

        // create MyEntity and add it to the scene
        this->entity = new MyEntity();
        scene.getDefaultLayer().add(this->entity);

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

#include <NasNas/thirdparty/entt/entt.hpp>
#include "NasNas/ecs/new/Registry.hpp"

struct Position { int x; int y; };
struct Velocity { int dx; int dy; };
struct Parent { ns::ecs::Entity entity; };
struct Children  { std::vector<ns::ecs::Entity> entities; };

struct BaseEntity {
    ns::ecs::Entity id;
    BaseEntity() {
        id = ns::Ecs.create();
    }

    template <class TComp, typename ...Targs>
    TComp& add(Targs ...args) {
        return ns::Ecs.attach<TComp>(id, args...);
    }
};

int main() {
    auto e1 = ns::Ecs.create();
    auto e2 = ns::Ecs.create();

    ns::Ecs.attach<Position>(e1);
    ns::Ecs.attach<Position>(e2);

    ns::Ecs.attach<Children>(e1).entities.emplace_back(e2);
    ns::Ecs.attach<Parent>(e1).entity = e1;
    ns::Ecs.attach<Parent>(e2).entity = e1;

    auto view1 = ns::Ecs.view<Position>();
    auto view2 = ns::Ecs.view<Position, Parent, Children>();

    BaseEntity ent;
    ent.add<Position>();
    auto& pos = ns::Ecs.get<Position>(ent.id);
    std::cout << ent.id << std::endl;

    for (auto& pos : ns::Ecs.getAll<Position>()) {
        pos.x += 2;
    }

    // Game g;
    // g.run();

    return 0;
}
