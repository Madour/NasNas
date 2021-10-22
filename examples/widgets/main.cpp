// Created by Modar Nasser on 10/10/2021.

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Ui.hpp>

struct Game : ns::App {
    ns::BitmapFont* m_font;
    ns::ui::Container m_gui;
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
        auto* btn = new ns::ui::Button<sf::RectangleShape>();
        btn->setBackground(*sprite);
        btn->setPosition(500, 300);
        btn->setOnHoverCallback([](auto& btn) { ns_LOG("hovered"); btn.scale(1.2f, 1.2f);});

        m_gui.m_widgets.push_back(btn);

        auto& scene = createScene("main");
        scene.getDefaultLayer().add(m_gui);

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

    std::make_unique<Game>()->run();

    ns::Res::dispose();
}
