// Created by Modar Nasser on 17/07/2021.

/**
* Created by Modar Nasser on 13/10/2020.
**/

#include <NasNas/Core.hpp>
#include <NasNas/Tween.hpp>

class Game : public ns::App {
    std::vector<ns::Tween> m_tweens;
    std::vector<sf::CircleShape> m_balls;

public:
    Game() : ns::App("Tweening example", {1280, 720}) {
        auto& scene = createScene("main");
        auto& camera = createCamera("main", 0);
        camera.lookAt(scene);

        auto* text = new sf::Text("Press R to replay", ns::Arial::getFont(), 24);
        text->setPosition(640-text->getGlobalBounds().width/2, 10);
        scene.getDefaultLayer().add(text);

        std::vector<ns::tween::EasingFunction> easing_functions = {
            ns::easing::linear,
            ns::easing::quadraticInOut,
            ns::easing::cubicInOut,
            ns::easing::circularInOut,
            ns::easing::exponentialInOut,
            ns::easing::backInOut,
            ns::easing::backInOut2,
            ns::easing::bounceOut,
            ns::easing::elasticOut,
        };
        std::vector<std::string> functions_names = {
            "Linear",
            "QuadraticInOut",
            "CubicInOut",
            "CircularInOut",
            "ExponentialInOut",
            "BackInOut",
            "BackInOut2",
            "BounceOut",
            "ElasticOut",
        };
        m_balls.resize(easing_functions.size());
        m_tweens.resize(easing_functions.size());

        auto ball_radius = 18.f;

        for (unsigned i = 0; i < easing_functions.size(); ++i) {
            auto* name = new sf::Text(functions_names[i], ns::Arial::getFont(), 20);
            name->setPosition(640-name->getGlobalBounds().width/2, float(60 + 75*i));
            scene.getDefaultLayer().add(name);

            m_balls[i].setRadius(ball_radius);
            m_balls[i].setFillColor(sf::Color::Red);
            m_balls[i].setOrigin(ball_radius, ball_radius);
            m_balls[i].setPosition(280, float(75 + 75*i));
            scene.getDefaultLayer().add(m_balls[i]);

            auto move_ball_fn = [this, i] (float v) {
                m_balls[i].setPosition(v, m_balls[i].getPosition().y);
            };

            m_tweens[i].loop().after(2.f)
                .apply(move_ball_fn).with(easing_functions[i])
                .from_to(280, 1000).during(2.f).delay(2.f)
                .to(280).during(2.f);
            m_tweens[i].onEnd([name]{ ns_LOG("Tween", name->getString().toAnsiString(), "ended.");});
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
