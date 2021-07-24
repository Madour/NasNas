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
            ns::easing::sinusoidalIntOut,
            ns::easing::quadraticInOut,
            ns::easing::custom::backIn<30>,
            ns::easing::custom::backIn2<30>,
            ns::easing::backInOut,
            ns::easing::custom::backInOut2<30>,
            ns::easing::bounceOut,
            ns::easing::custom::elasticOut<25>,
        };
        std::vector<std::string> functions_names = {
            "Linear",
            "SinusoidalInOut",
            "QuadraticInOut",
            "BackIn<30>",
            "BackIn2<30>",
            "BackInOut",
            "BackInOut2<30>",
            "BounceOut",
            "ElasticOut",
        };
        m_balls.resize(m_functions.size());
        m_tweens.resize(m_functions.size());

        auto ball_radius = 18.f;

        for (unsigned i = 0; i < m_functions.size(); ++i) {
            auto* name = new sf::Text(functions_names[i], ns::Arial::getFont(), 20);
            name->setPosition(640-name->getGlobalBounds().width/2, float(60 + 75*i));
            scene.getDefaultLayer().add(name);

            m_balls[i].setRadius(ball_radius);
            m_balls[i].setFillColor(sf::Color::Red);
            m_balls[i].setOrigin(ball_radius, ball_radius);
            m_balls[i].setPosition(50, float(75 + 75*i));
            scene.getDefaultLayer().add(m_balls[i]);

            auto move_ball_fn = [this, i] (float v) {
                m_balls[i].setPosition(v, m_balls[i].getPosition().y);
            };

            m_tweens[i].loop()
                .apply(move_ball_fn)
                .from_to(280, 1000).during(2.f).with(m_functions[i]).delay(2.f)
                .to(280).during(2.f).delay(2.f);
        }
    }

    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        if (event.type == sf::Event::KeyPressed)
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
