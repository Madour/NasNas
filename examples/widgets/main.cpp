// Created by Modar Nasser on 10/10/2021.

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Ui.hpp>

struct Game : ns::App {
    ns::BitmapFont* m_font;
    ns::ui::GuiRoot m_gui;
    ns::ui::NineSlice nineslice;
    Game() : ns::App("Widgets example", {1280, 720}) {
        // create a BitmapFont
        m_font = new ns::BitmapFont(
                ns::Res::getTexture("font.png"),
                {8, 8},
                " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;!?-+=",
                {{"ABCDEFGHIJKMNOPQRSTUVWXYZ?=-", 7}, {"ijlntsofpqrux", 5}},
                6
        );

        auto& scene = createScene("main");
        //scene.getDefaultLayer().add(nineslice);

        auto& cam = createCamera("main", 0);
        cam.lookAt(scene);
        m_gui.setCamera(cam);

        auto* rt = new sf::RenderTexture();
        rt->create(1280, 720);
        rt->clear();
        int step = 50;
        for (int x = 0; x < 1280; x+=step)
            for (int y = 0; y < 720; y+=step) {
                auto r = sf::RectangleShape(sf::Vector2f(step, step));
                r.setFillColor(sf::Color(200, 200, 200));
                r.setOutlineColor(sf::Color(50, 50, 50));
                r.setOutlineThickness(1);
                r.setPosition(x, y);
                rt->draw(r);
            }
        rt->display();
        scene.getDefaultLayer().add(new sf::Sprite(rt->getTexture()));
        scene.getDefaultLayer().add(m_gui);

        auto* sprite = new sf::RectangleShape();
        sprite->setFillColor(sf::Color::Yellow);
        sprite->setSize({150, 50});
        sprite->setOrigin(75, 25);
        auto* sprite2 = new sf::RectangleShape();
        sprite2->setFillColor(sf::Color::Red);
        sprite2->setSize({200, 50});
        sprite2->setOrigin(100, 25);

        auto& container2 = m_gui.addWidget<ns::ui::Container>();
        container2.setPosition(250, 100);
        container2.setStyle({{50, 32, 50, 32}, &nineslice});
        container2.setSize(500, 300);
        auto& btn01 = container2.addWidget<ns::ui::Button<sf::CircleShape>>();
        auto*cs1=new sf::CircleShape(150);
        cs1->setOrigin(cs1->getRadius(), cs1->getRadius());
        cs1->setFillColor(sf::Color(180, 180, 180));
        btn01.setBackground(*cs1);

        auto& btn02 = container2.addWidget<ns::ui::Button<sf::CircleShape>>();
        auto*cs2=new sf::CircleShape(150);
        cs2->setOrigin(cs2->getRadius(), cs2->getRadius());
        cs2->setFillColor(sf::Color(180, 180, 180));
        btn02.setBackground(*cs2);
        btn02.setPosition(500, 300);

        auto& btn = container2.addWidget<ns::ui::Button<sf::RectangleShape>>();
        btn.setBackground(*sprite);
        btn.setPosition(150, 100);

        sf::Text btn_text;
        btn_text.setString("Click here");
        btn_text.setFont(ns::Arial::getFont());
        btn_text.setCharacterSize(25);
        btn_text.setOrigin(btn_text.getGlobalBounds().width/2, btn_text.getGlobalBounds().height/2+5);
        btn_text.setFillColor(sf::Color::Black);
        btn.setText(btn_text);
        btn.setCallback(ns::ui::Callback::onHover, [](auto* btn) {btn->setScale(1.1f, 1.1f);});
        btn.setCallback(ns::ui::Callback::onUnhover, [](auto* btn) {btn->setScale(1.f, 1.f);});
        btn.setCallback(ns::ui::Callback::onFocus, [sprite2](auto* btn) {
            auto* b = dynamic_cast<ns::ui::Button<sf::RectangleShape>*>(btn);
            b->setBackground(*sprite2);
        });
        btn.setCallback(ns::ui::Callback::onUnfocus, [sprite](auto* btn) {
            auto* b = dynamic_cast<ns::ui::Button<sf::RectangleShape>*>(btn);
            b->setBackground(*sprite);
        });
        btn.setCallback(ns::ui::Callback::onLeftClickPress, [](auto* btn) {ns_LOG("Btn left click press");});
        btn.setCallback(ns::ui::Callback::onLeftClickRelease, [](auto* btn) {ns_LOG("Btn left click release");});
        btn.setCallback(ns::ui::Callback::onMiddleClickPress, [](auto* btn) {ns_LOG("Btn middle click press");});
        btn.setCallback(ns::ui::Callback::onMiddleClickRelease, [](auto* btn) {ns_LOG("Btn middle click release");});

        nineslice.setMode(ns::ui::NineSlice::Mode::Repeat);
        nineslice.setTexture(ns::Res::getTexture("tileset.png"));
        nineslice.setTextureRect({16, 0, 16*5, 16*5});
        nineslice.setSlices(32, 32, 32, 32);
        nineslice.setSize(500-64, 300-64);
        nineslice.setPosition(0, 0);

        addDebugText<sf::Vector2f>("mouse pos", [&] { return getMousePosition(getCamera("main")); }, {10, 10});
    }
    void onEvent(const sf::Event& event) override {
        ns::App::onEvent(event);
        m_gui.onEvent(event);
    }
    void update() override {
    }
};

int main() {
    ns::Res::load("assets");

    Game g;
    g.run();

    ns::Res::dispose();
}
