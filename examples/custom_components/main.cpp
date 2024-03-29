/**
* Created by Modar Nasser on 06/02/2020.
**/

#include <algorithm>
#include <NasNas/Core.hpp>
#include <NasNas/Ecs.hpp>

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

class HpBar : public ns::EntityObject, public sf::Drawable {
public:
    HpBar() {
        add<sf::Transformable>().setPosition(540, 300);

        // add the custom component
        add<HpComponent>(500, 500);

        // add a RectangleShape component to represent the HP bar
        sf::RectangleShape hp_bar{{0, 20}};
        hp_bar.setFillColor(sf::Color::Red);
        hp_bar.setOrigin(250, 10);
        add<ns::ecs::RectangleShape>(hp_bar);
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        states.transform *= get<sf::Transformable>().getTransform();
        target.draw(get<ns::ecs::RectangleShape>().getDrawable(), states);
    }
};

class Game : public ns::App {
    HpBar hp_bar;
    ns::ecs::System<HpComponent> hp_system;
public:

    Game() : ns::App("Custom component example", {1080, 720}) {
        // create a scene and a camera
        auto& scene = this->createScene("main");
        auto& camera = this->createCamera("main", 0);
        camera.lookAt(scene);

        // add inputs components to the hp_bar
        auto& inputs_comp = this->hp_bar.add<ns::ecs::InputsComponent>();
        inputs_comp.onPress(sf::Keyboard::Space, [this](){ this->hp_bar.get<HpComponent>().damage(50); });
        inputs_comp.enable();

        // add hp_bar to the scene
        scene.getDefaultLayer().add(this->hp_bar);

        // set the Hp system
        hp_system = [](auto& hp) { hp.restore(1); };
    }

    void update() override {
        // run Inputs system
        ns::Ecs.run<ns::ecs::InputsComponent>([](auto& input) {
            input.update();
        });

        // run HP system
        ns::Ecs.run(hp_system);

        // run HP drawable system
        ns::Ecs.run<HpComponent, ns::ecs::RectangleShape>([](auto& hp_comp, auto& rectangle) {
            rectangle.getDrawable().setSize({static_cast<float>(hp_comp.hp), 20.f});
        });
    }
};

int main() {

    Game g;
    g.run();

    return 0;
}
