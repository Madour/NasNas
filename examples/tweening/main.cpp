// Created by Modar Nasser on 17/07/2021.

/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas/Core.hpp>
#include <NasNas/Tween.hpp>

class Game : public ns::App {
    std::vector<ns::tween::EasingFunction> m_functions;
    std::vector<ns::tween::Tween> m_tweens;
    std::vector<sf::CircleShape> m_balls;

public:
    Game() : ns::App("Tweening Demo", {1280, 720}, 1, 60, 60) {
        auto& scene = createScene("main");
        auto& camera = createCamera("main", 0);
        camera.lookAt(scene);

        auto* text = new sf::Text("Press R to replay", ns::Arial::getFont(), 24);
        text->setPosition(640-text->getGlobalBounds().width/2, 10);
        scene.getDefaultLayer().add(text);

        m_functions = {
            ns::easing::linear,
            //ns::easing::sinusoidalIntOut,
            //ns::easing::quadraticInOut,
            ns::easing::custom::backIn<30>,
            ns::easing::custom::backIn2<3>,
            ns::easing::backInOut,
            ns::easing::custom::backInOut2<3>,
            ns::easing::bounceOut,
            ns::easing::elasticOut,
        };
        m_balls.resize(m_functions.size());
        m_tweens.resize(m_functions.size());

        auto ball_radius = 25.f;
        auto d = 2.f;
        auto s = 300.f;
        auto e = 1000.f;

        for (unsigned i = 0; i < m_functions.size(); ++i) {
            m_balls[i].setRadius(ball_radius);
            m_balls[i].setFillColor(sf::Color::Red);
            m_balls[i].setOrigin(ball_radius, ball_radius);
            m_balls[i].setPosition(50, float(80 + 100*i));
            scene.getDefaultLayer().add(m_balls[i]);

            m_tweens[i].from(s).to(e).during(d).with(m_functions[i]).apply([this, i](float v){
                auto& ball = this->m_balls[i];
                ball.setPosition(v, ball.getPosition().y);
            });
        }
    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::KeyReleased)
            if (event.key.code == sf::Keyboard::R)
                for (auto& tween : m_tweens)
                    tween.restart();
    }

    void update() override {
        for (unsigned i = 0; i < m_tweens.size(); ++i) {
            auto t = m_tweens[i].step();
            m_balls[i].setFillColor({sf::Uint8(255-t*255), sf::Uint8(t*255), 0});
        }
    }
};

int main() {
    Game g;
    g.run();
    return 0;
}
