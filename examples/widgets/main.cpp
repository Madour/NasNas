// Created by Modar Nasser on 10/10/2021.

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Ui.hpp>

struct Game : ns::App {
    ns::BitmapFont* m_font;
    ns::ui::Container m_gui;
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

        auto* sprite = new sf::RectangleShape();
        sprite->setFillColor(sf::Color::Yellow);
        sprite->setSize({200, 50});
        auto* sprite2 = new sf::RectangleShape();
        sprite2->setFillColor(sf::Color::Red);
        sprite2->setSize({200, 50});

        auto& btn = m_gui.addWidget<ns::ui::Button<sf::RectangleShape>>();
        btn.setBackground(*sprite);
        btn.setPosition(500, 300);
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

        auto& scene = createScene("main");
        scene.getDefaultLayer().add(m_gui);
        scene.getDefaultLayer().add(nineslice);

        auto& cam = createCamera("main", 0);
        cam.lookAt(scene);
        m_gui.setCamera(cam);
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
