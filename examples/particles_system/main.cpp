/**
* Created by Modar Nasser on 14/02/2020.
**/

#include <NasNas.h>

class MyCustomParticleSystem : public ns::ParticleSystem {
public:
    MyCustomParticleSystem() = default;
    void onParticleCreate(ns::Particle& particle) override {
        auto s = ns::utils::getRandomFloat(0.f, 1.5f);
        auto a = ns::utils::getRandomFloat(0.f, 360.f);
        particle.color.a = ns::utils::getRandomInt(0, 255);
        particle.scale = 2.f;
        particle.rotation = a;
        particle.velocity.x = s*std::cos(ns::to_radian(a));
        particle.velocity.y = std::abs(s*std::sin(ns::to_radian(a)));
        particle.lifetime = ns::utils::getRandomFloat(1.f, 4.f);
    }

    void onParticleUpdate(ns::Particle& particle) override {
        particle.rotation += 0.1f;
        particle.color.a = (1.f-(particle.getAge()/particle.lifetime))*255;
        particle.velocity.y += 0.02f;
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

        m_particles_system.setEmmitRate(15.f);
        m_particles_system.setTexture(ns::Res::getTexture("tileset.png"));
        m_particles_system.setPosition(500, 300);
        m_particles_system.emmit({240, 16, 16, 16}, 20, true);
        scene->getDefaultLayer()->addRaw(&m_particles_system);

        addDebugText<unsigned>("Particles count :", [&]{return m_particles_system.getParticleCount();}, {0, 0});
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
            m_particles_system.emmit({240, 0, 16, 16}, 500, true);
        }
    }

    void update() override {
        auto mouse_pos = getWindow().mapPixelToCoords(sf::Mouse::getPosition(getWindow()), *getCamera("main"));
        m_particles_system.setPosition(mouse_pos);
        m_particles_system.update();
    }
};

int main() {
    srand(time(nullptr));

    ns::Res::load("assets");

    ns::Config::Window::update_rate = 60;

    Game g;
    g.run();

    ns::Res::dispose();

    return 0;
}
