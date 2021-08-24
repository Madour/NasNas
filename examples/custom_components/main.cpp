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

        auto ent = ns::Ecs.create();
        auto& inputs = ns::Ecs.attach<ns::ecs::InputsComponent>(ent);
        inputs.onPress(sf::Keyboard::Q, [&ent](){std::cout << ent << " : Q pressed\n"; });
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
                this->entity->get<HpComponent>()->damage(50);
            }
        }
    }

    void update() override {
        this->entity->update();
        auto inputs_view = ns::Ecs.view<ns::ecs::InputsComponent>();
        inputs_view.for_each([&](ns::ecs::InputsComponent& inputs) {
            inputs.update();
        });
    }
};


struct Position { int x; int y; };
struct Velocity { int dx; int dy; };
struct Rotation { int da; };

std::ostream& operator<<(std::ostream& os, Position& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}


std::ostream& operator<<(std::ostream& os, Velocity& v) {
    os << "(" << v.dx << ", " << v.dy << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, Rotation& r) {
    os  << r.da << " deg";
    return os;
}

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
    auto e0 = ns::Ecs.create();
    auto e1 = ns::Ecs.create();
    auto e2 = ns::Ecs.create();

    ns::Ecs.attach<Position>(e0).x = 1;
    ns::Ecs.attach<Rotation>(e0).da = 1;

    ns::Ecs.attach<Position>(e1).x = 2;
    ns::Ecs.attach<Velocity>(e1).dx = 2;

    ns::Ecs.attach<Position>(e2).x = 3;
    ns::Ecs.attach<Velocity>(e2).dy = 3;
    ns::Ecs.attach<Rotation>(e2).da = 3;

    ns::Ecs.view<Position, Rotation>().for_each([](ns::ecs::Entity e, Position& p, Rotation& r) {
        std::cout << "Entity " << e << " at " << p << " rotated by " << r << "\n";
    });

    std::cout << "-----" << std::endl;

    auto pos_vel_view = ns::Ecs.view<Position, Velocity>();
    pos_vel_view.for_each([&](ns::ecs::Entity e) {
        auto [pos, vel] = pos_vel_view.get(e);
        std::cout << "Entity " << e << " has Position " << pos << " and Velocity " << vel << "\n";
    });

    std::cout << "-----" << std::endl;

    ns::Ecs.view<Position, Velocity, Rotation>().for_each([](Position& p, Velocity& v, Rotation& r) {
        std::cout << "Rotation : " << r << " ; Position : "<< p << " ; Velocity : " << v << " \n";
    });

    Game g;
    g.run();

    return 0;
}
