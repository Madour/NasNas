#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <NasNas/NasNas>

const std::string tilemap_string = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                   "<map version=\"1.5\" tiledversion=\"1.7.0\" orientation=\"orthogonal\" renderorder=\"right-down\" width=\"20\" height=\"20\" tilewidth=\"16\" tileheight=\"16\" infinite=\"0\" nextlayerid=\"2\" nextobjectid=\"1\">\n"
                                   " <tileset firstgid=\"1\" name=\"tileset\" tilewidth=\"16\" tileheight=\"16\" tilecount=\"322\" columns=\"23\">\n"
                                   "  <image source=\"tileset.png\" width=\"368\" height=\"224\"/>\n"
                                   " </tileset>\n"
                                   " <layer id=\"1\" name=\"bg\" width=\"20\" height=\"20\">\n"
                                   "  <data encoding=\"csv\">\n"
                                   "1,1,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,\n"
                                   "1,1,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,\n"
                                   "1,1,152,152,152,152,4,4,4,4,4,4,4,4,152,152,152,152,152,152,\n"
                                   "1,1,152,152,4,4,4,4,152,152,152,152,152,152,152,152,152,152,152,152,\n"
                                   "1,1,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,\n"
                                   "1,1,152,4,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,\n"
                                   "152,1,152,152,4,152,152,152,152,152,152,152,152,152,152,152,152,152,152,152,\n"
                                   "152,152,152,152,152,4,152,152,152,152,152,152,152,152,152,152,152,152,152,152,\n"
                                   "152,152,152,152,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,152,\n"
                                   "4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,152,152,152,\n"
                                   "152,152,152,152,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,\n"
                                   "152,152,152,152,152,4,4,4,4,4,4,4,152,152,152,152,152,152,152,152,\n"
                                   "152,152,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,\n"
                                   "152,152,152,152,152,152,152,152,152,4,152,152,152,152,152,152,152,152,152,152,\n"
                                   "152,152,152,152,152,152,152,152,152,4,152,152,152,152,152,152,152,152,152,152,\n"
                                   "152,152,152,152,152,152,152,152,152,4,152,152,152,152,152,152,152,152,152,152,\n"
                                   "152,152,152,152,152,152,152,152,152,152,4,152,152,152,152,152,152,152,152,152,\n"
                                   "152,152,152,152,152,152,152,152,152,152,4,152,152,152,152,152,152,152,152,152,\n"
                                   "152,4,152,152,152,152,152,152,152,4,4,152,152,152,152,152,152,152,152,152,\n"
                                   "152,152,4,4,4,4,4,4,4,152,152,152,152,152,152,152,152,152,152,152\n"
                                   "</data>\n"
                                   " </layer>\n"
                                   "</map>";


class Game : public ns::App {
    ns::Tween tween;
    sf::Texture logo_tex;
    sf::Sprite logo;
    ns::tm::TiledMap tilemap;
    sf::Music music;
    sf::CircleShape cursor;

    sf::Text btn_landscape;
    sf::Text btn_portrait;

public:
    Game() : ns::App("NasNas android !", {1280, 720}) {
        ns::Settings::debug_mode.show_bounds = false;
        ns::Settings::debug_mode.show_fps = false;
        ns::Settings::debug_mode = true;

        auto& scene = createScene("main");
        auto& cam = createCamera("main", 0);
        cam.lookAt(scene);

        music.openFromFile("canary.wav");

        tilemap.loadFromString(tilemap_string);
        tilemap.getTileLayer("bg").scale(4, 4);

        logo_tex.loadFromFile("image.png");
        logo.setTexture(logo_tex);
        logo.setOrigin(logo_tex.getSize().x/2.f, logo_tex.getSize().y);

        auto& view_size = ns::Settings::getConfig().getViewSize();
        auto tween_move_logo = [&](float val) {
            logo.setPosition(view_size.x/2.f, val);
        };
        auto tween_scale_logo = [&](float val) {
            logo.setScale(1.f, val);
        };

        tween.loop().from_to(150, 720).during(1.f).with(ns::easing::bounceOut).apply(tween_move_logo).delay(0.5f)
                    .from_to(1.f, 0.5f).during(0.2f).with(ns::easing::sinusoidalOut).apply(tween_scale_logo)
                    .from_to(0.5f, 1.f).during(0.05f).with(ns::easing::linear).apply(tween_scale_logo)
                    .from_to(720, 150).apply(tween_move_logo).with(ns::easing::quadraticOut).delay(0.5f);

        cursor.setRadius(35.f);
        cursor.setOrigin(cursor.getRadius(), cursor.getRadius());
        cursor.setFillColor({255, 255, 255, 180});

        btn_landscape.setFont(ns::Arial::getFont());
        btn_landscape.setString("Landscape");
        btn_landscape.setCharacterSize(50);
        btn_landscape.setStyle(sf::Text::Bold);
        btn_landscape.setPosition(100, 300);

        btn_portrait.setFont(ns::Arial::getFont());
        btn_portrait.setString("Portrait");
        btn_portrait.setCharacterSize(50);
        btn_portrait.setStyle(sf::Text::Bold);
        btn_portrait.setPosition(100, 600);

        scene.getDefaultLayer().add(tilemap.getTileLayer("bg"));
        scene.getDefaultLayer().add(logo);
        scene.getDefaultLayer().add(cursor);
        scene.getDefaultLayer().add(btn_landscape);
        scene.getDefaultLayer().add(btn_portrait);

        addDebugText<sf::Vector2u>("window size", [&]{ return getWindow().getSize(); }, {10, 10});
        addDebugText<sf::Vector2f>("sf::Touch 0", [&]{ return getTouchPosition(0); }, {10, 50});
        addDebugText<sf::Vector2f>("sf::Touch 1", [&]{ return getTouchPosition(1); }, {10, 90});
        addDebugText<sf::Vector2f>("sf::Touch 2", [&]{ return getTouchPosition(2); }, {10, 130});
    }

    void onEvent(const sf::Event& event) override {
        if (event.type == sf::Event::Closed) {
            getWindow().close();
        }
        else if (event.type == sf::Event::MouseLeft)
            sleep();
        else if (event.type == sf::Event::MouseEntered)
            awake();

        else if (event.type == sf::Event::TouchBegan) {
            ns::android::vibrate(100);
            music.stop();
            music.play();
            auto touch_pos = getTouchPosition(0, getCamera("main"));
            if (btn_landscape.getGlobalBounds().contains(touch_pos)) {
                ns::android::setScreenOrientation(ns::android::Landscape);
            }
            if (btn_portrait.getGlobalBounds().contains(touch_pos)) {
                ns::android::setScreenOrientation(ns::android::Portrait);
            }

        }
    }

    void update() override {
        if (sf::Touch::isDown(0)) {
            cursor.setPosition(getTouchPosition(0, getCamera("main")));
        }
        tween.step();
    }
};


int main() {
    ns::android::init();
    ns::android::hideStatusBar();
    ns::android::hideNavigation();

    Game g;
    g.run();
}
