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
        scene.getDefaultLayer().add(new sf::Sprite(rt->getTexture()));
        scene.getDefaultLayer().add(m_gui);

        auto* sprite = new sf::RectangleShape();
        sprite->setFillColor(sf::Color::Yellow);
        sprite->setSize({40, 40});
        auto* sprite2 = new sf::RectangleShape();
        sprite2->setFillColor(sf::Color::Red);
        sprite2->setSize({200, 50});

        auto& container = m_gui.addWidget<ns::ui::Container>();
        container.setSize(825, 400);
        container.setPosition(75, 50);

        auto& container2 = container.addWidget<ns::ui::Container>();
        container2.setSize(412, 200);
        container2.setPosition(95, 60);
        auto& btn = container2.addWidget<ns::ui::Button<sf::RectangleShape>>();
        btn.setBackground(*sprite);
        btn.setPosition(50, 25);
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
        nineslice.setTextureRect({32, 16, 48, 48});
        nineslice.setSlices(16, 16, 16, 16);
        nineslice.setSize(200, 45);
        nineslice.setPosition(20, 20);
        nineslice.scale(2.f, 2.f);

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
