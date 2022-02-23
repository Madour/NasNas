// Created by Modar Nasser on 10/10/2021.

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>
#include <NasNas/Ui.hpp>

struct Game : ns::App {
    ns::ui::GuiRoot m_gui;
    ns::ui::NineSlice nineslice;
    ns::ui::Button* m_btn;
    Game() : ns::App("Widgets example", {1280, 720}) {
        auto& scene = createScene("main");
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

        auto* cs1 = new sf::CircleShape(150);
        cs1->setOrigin(cs1->getRadius(), cs1->getRadius());
        cs1->setFillColor(sf::Color(180, 180, 180));

        auto* cs2 = new sf::CircleShape(150);
        cs2->setOrigin(cs2->getRadius(), cs2->getRadius());
        cs2->setFillColor(sf::Color(120, 120, 180));

        auto& container2 = m_gui.addWidget<ns::ui::Container>();
        container2.setPosition(250, 100);
        container2.style = {{50, 32, 50, 32}, &nineslice};
        container2.setSize(500, 300);

        auto circlebtn_style = ns::ui::Button::Style{{0, 0, 0, 0, cs1}, cs2, nullptr, new ns::ui::CircleRegion(150)};

        auto& btn01 = container2.addWidget<ns::ui::Button>();
        btn01.setPosition(0, 0);
        btn01.style = circlebtn_style;

        auto& btn02 = container2.addWidget<ns::ui::Button>();
        btn02.setPosition(500, 300);
        btn02.style = circlebtn_style;

        auto& btn = container2.addWidget<ns::ui::Button>();
        btn.setPosition(150, 100);
        btn.style = {{0, 0, 0, 10, sprite}, sprite, sprite2, new ns::ui::RectangleRegion(150, 50)};
        m_btn = &btn;
        btn.text.setString("Click here");
        btn.text.setFont(ns::Arial::getFont());
        btn.text.setCharacterSize(25);
        btn.text.setFillColor(sf::Color::Black);
        btn.setTextAlign(ns::ui::TextAlign::Left);
        btn.setCallback(ns::ui::CursorCallback::onHover, [](auto* btn) {btn->setScale(1.1f, 1.1f); dynamic_cast<ns::ui::Button*>(btn)->text.rotate(-10.f);});
        btn.setCallback(ns::ui::CursorCallback::onUnhover, [](auto* btn) {btn->setScale(1.f, 1.f); dynamic_cast<ns::ui::Button*>(btn)->text.rotate(+10.f);});

        btn.setCallback(ns::ui::ClickCallback::onLeftClickPress, [](auto* btn) {ns_LOG("Btn left click press");});
        btn.setCallback(ns::ui::ClickCallback::onLeftClickRelease, [](auto* btn) {ns_LOG("Btn left click release");});
        btn.setCallback(ns::ui::ClickCallback::onMiddleClickPress, [](auto* btn) {ns_LOG("Btn middle click press");});
        btn.setCallback(ns::ui::ClickCallback::onMiddleClickRelease, [](auto* btn) {ns_LOG("Btn middle click release");});

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
        if (ns::Inputs::isKeyDown(sf::Keyboard::Left))
            m_btn->setTextAlign(ns::ui::TextAlign::Left);
        if (ns::Inputs::isKeyDown(sf::Keyboard::Up))
            m_btn->setTextAlign(ns::ui::TextAlign::Center);
        if (ns::Inputs::isKeyDown(sf::Keyboard::Right))
            m_btn->setTextAlign(ns::ui::TextAlign::Right);
    }
};

int main() {
    ns::Res::load("assets");

    Game g;
    g.run();

    ns::Res::dispose();
}
