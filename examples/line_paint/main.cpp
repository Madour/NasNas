// Created by Modar Nasser on 25/04/2021.

#include <NasNas/Core.hpp>

class Game : public ns::App {
    sf::CircleShape cursor;
    ns::LineShape line;
public:
    Game() : ns::App("Line paint example", {1280, 720}) {
        getWindow().setClearColor(sf::Color(225, 240, 240));
        getWindow().setMouseCursorVisible(false);

        // create a scene and a camera
        auto& scene = this->createScene("main");
        auto& camera = this->createCamera("main", 0);
        camera.lookAt(scene);

        this->line.setThickness(10.f);

        this->cursor.setRadius(this->line.getThickness() / 2.f);
        this->cursor.setOrigin(this->cursor.getRadius(), this->cursor.getRadius());
        this->cursor.setOutlineColor(sf::Color::Black);

        scene.getDefaultLayer().add(this->cursor);
        scene.getDefaultLayer().add(this->line);

        addDebugText<float>("Line thickness : ", [&]{return this->line.getThickness();}, {10, 10});
        addDebugText<size_t>("  Points count : ", [&]{return this->line.getPointCount();}, {10, 40});
    }

    void onEvent(const sf::Event& event) override {
        static bool mouse_grab  = false;
        static bool pen_down    = false;
        static auto color       = sf::Color::White;
        static auto mouse_pos   = getMousePosition();
        static sf::Clock clock;

        if (clock.getElapsedTime().asMilliseconds() > 200) {
            color = sf::Color(rand()%255, rand()%255, rand()%255);
            clock.restart();
            this->cursor.setFillColor(color);
        }

        ns::App::onEvent(event);
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                getCamera("main").zoom(0.90f);
            } else {
                getCamera("main").zoom(1.1f);
            }
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R)
                getCamera("main").setSize(1080, 720);
            if (event.key.code == sf::Keyboard::Space) {
                mouse_grab = true;
            }
        }
        else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Space) {
                mouse_grab = false;
            }
            else if (event.key.code == sf::Keyboard::Add) {
                this->line.setThickness(this->line.getThickness() + 2);
                this->line.setOutlineThickness(this->line.getOutlineThickness() + 2);
            }
            else if (event.key.code == sf::Keyboard::Subtract) {
                this->line.setThickness(this->line.getThickness() - 2);
                this->line.setOutlineThickness(this->line.getOutlineThickness() - 2);
            }
            else if (event.key.code == sf::Keyboard::Multiply) {
                this->line.setThickness(this->line.getThickness() * 2);
            }
            else if (event.key.code == sf::Keyboard::Divide) {
                this->line.setThickness(this->line.getThickness() / 2);
            }
            this->cursor.setRadius(this->line.getThickness() / 2.f);
            this->cursor.setOrigin(this->cursor.getRadius(), this->cursor.getRadius());
            this->cursor.setOutlineThickness(line.getOutlineThickness());
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Button::Middle)
                mouse_grab = true;
            else
                pen_down = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Button::Middle)
                mouse_grab = false;
            else {
                pen_down = false;
                this->line.addPoint(getMousePosition(getCamera("main")) - this->line.getPosition(), color);
                this->line.addPoint(getMousePosition(getCamera("main")) - this->line.getPosition(), color);
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            if (mouse_grab) {
                auto delta = sf::Vector2f(mouse_pos.x-event.mouseMove.x, mouse_pos.y-event.mouseMove.y);
                delta /= 1280 / getCamera("main").getSize().x;
                getCamera("main").move(delta);
            }
            else if (pen_down) {
                this->line.addPoint(getMousePosition(getCamera("main")) - this->line.getPosition(), color);
            }
        }
        mouse_pos = getMousePosition();
    }

    void update() override {
        this->cursor.setPosition(getMousePosition(getCamera("main")));
    }
};

int main() {
    srand((unsigned)time(nullptr));

    ns::Settings::debug_mode = true;
    ns::Settings::debug_mode.show_bounds = false;

    Game g;
    g.run();

    return 0;
}
