/**
* Created by Modar Nasser on 14/02/2020.
**/

#include <NasNas.h>

class MyCustomParticleSystem : public ns::ParticleSystem {
public:
    MyCustomParticleSystem() = default;
    void onParticleCreate(ns::Particle& particle) override {
        auto r = ns::ParticleSystem::getRandomFloat();
        auto a = (float)(rand()%360);
        particle.color.a = rand()%255;
        particle.scale = 1.5f;
        particle.rotation = (float)(rand()%360);
        particle.velocity.x = r*std::cos(ns::to_radian(a));
        particle.velocity.y = r*std::sin(ns::to_radian(a));
    }

    void onParticleUpdate(ns::Particle& particle) override {
        particle.rotation+=0.1f;
        particle.color.a -= 1;
        particle.velocity.y += 3*0.008f;
    }

    bool isParticleDead(ns::Particle& particle) override {
        return particle.color.a <= 0;
    }

};


class Game : public ns::App {
    MyCustomParticleSystem m_particles_system;
public:
    Game() : ns::App("Particles System", {1080, 720}) {

        // create a scene and a camera
        auto* scene = this->createScene("main");
        auto* camera = this->createCamera("main", 0);
        camera->lookAt(scene);

        m_particles_system.setTexture(ns::Res::getTexture("tileset.png"));
        m_particles_system.setPosition(500, 300);
        m_particles_system.emmit({240, 16, 16, 16}, 1000, true);
        scene->getDefaultLayer()->addRaw(&m_particles_system);
    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0)
                getCamera("main")->zoom(0.95);
            else
                getCamera("main")->zoom(1.05);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            m_particles_system.emmit({240, 0, 16, 16}, 500, false);
        }
    }

    void update() override {
        m_particles_system.setPosition(getWindow().mapPixelToCoords(sf::Mouse::getPosition(getWindow()), *getCamera("main")));
        m_particles_system.update();
    }
};

int main() {
    srand(time(0));

    ns::Res::load("assets");

    ns::Config::Window::update_rate = 60;

    Game g;
    g.run();

    ns::Res::dispose();

    return 0;
}
