#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <NasNas/NasNas>


class Game : public ns::App {
    ns::Tween tween;
    sf::Texture logo_tex;
    sf::Sprite logo;
    ns::tm::TiledMap tilemap;
    sf::Music music;
    sf::CircleShape cursor;

    ns::ui::GuiRoot m_gui;

    sf::RectangleShape btn_bg;
    sf::RectangleShape btn_bg_focused;

public:
    Game() : ns::App("NasNas android !", {1280, 720}) {
        ns::Settings::debug_mode.show_bounds = false;
        ns::Settings::debug_mode.show_fps = false;
        ns::Settings::debug_mode = true;

        auto& scene = createScene("main");
        auto& cam = createCamera("main", 0);
        cam.lookAt(scene);
        m_gui.setCamera(cam);

        music.openFromFile("canary.wav");

        tilemap.loadFromFile("simple_map.tmx");
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
        cursor.setFillColor({180, 180, 180, 180});

        btn_bg.setSize({300, 150});
        btn_bg.setOrigin(150, 75);
        btn_bg.setFillColor({250, 190, 0});

        btn_bg_focused.setSize({300, 150});
        btn_bg_focused.setOrigin(150, 75);
        btn_bg_focused.setFillColor({255, 238, 46});

        ns::ui::Button::Style btn_style;
        btn_style.padding = {25, 25, 25, 25};
        btn_style.drawable = &btn_bg;
        btn_style.drawable_focused = &btn_bg_focused;
        btn_style.region = new ns::ui::RectangleRegion(300, 150);

        auto btn_text = sf::Text("", ns::Arial::getFont());
        btn_text.setCharacterSize(32);
        btn_text.setFillColor(sf::Color::Black);

        auto& btn_landscape = m_gui.addWidget<ns::ui::Button>();
        btn_landscape.style = btn_style;
        btn_landscape.text = btn_text;
        btn_landscape.text.setString("Landscape");
        btn_landscape.setTextAlign(ns::ui::TextAlign::Left);
        btn_landscape.setPosition(300, 150);
        btn_landscape.setCallback(ns::ui::ClickCallback::onTouchEnded, [](auto* w) { ns::android::setScreenOrientation(ns::android::ScreenOrientation::Landscape); });

        auto& btn_portrait = m_gui.addWidget<ns::ui::Button>();
        btn_portrait.style = btn_style;
        btn_portrait.text = btn_text;
        btn_portrait.text.setString("Portrait");
        btn_portrait.setTextAlign(ns::ui::TextAlign::Right);
        btn_portrait.setPosition(300, 350);
        btn_portrait.setCallback(ns::ui::ClickCallback::onTouchEnded, [](auto* w) { ns::android::setScreenOrientation(ns::android::ScreenOrientation::Portrait); });

        auto& btn_play_audio = m_gui.addWidget<ns::ui::Button>();
        btn_play_audio.style = btn_style;
        btn_play_audio.text = btn_text;
        btn_play_audio.text.setString("Play audio");
        btn_play_audio.setTextAlign(ns::ui::TextAlign::Center);
        btn_play_audio.setPosition(300, 550);
        btn_play_audio.setCallback(ns::ui::ClickCallback::onTouchEnded, [&](auto* w) { music.stop(); music.play(); });

        scene.getDefaultLayer().add(tilemap.getTileLayer("bg"));
        scene.getDefaultLayer().add(logo);
        scene.getDefaultLayer().add(m_gui);
        scene.getDefaultLayer().add(cursor);


        ns_LOG("Test printing to logcat.", "Run `adb logcat | grep ns_LOG` to see output !");

        addDebugText<sf::Vector2u>("window size", [&]{ return getWindow().getSize(); }, {10, 10});
        addDebugText<sf::Vector2f>("sf::Touch 0", [&]{ return getTouchPosition(0); }, {10, 50});
        addDebugText<sf::Vector2f>("sf::Touch 1", [&]{ return getTouchPosition(1); }, {10, 90});
        addDebugText<sf::Vector2f>("sf::Touch 2", [&]{ return getTouchPosition(2); }, {10, 130});
    }

    void onEvent(const sf::Event& event) override {
        static bool music_paused = false;
        m_gui.onEvent(event);
        if (event.type == sf::Event::Closed) {
            getWindow().close();
        }
        else if (event.type == sf::Event::MouseLeft) {
            music.pause();
            music_paused = true;
            sleep();
        }
        else if (event.type == sf::Event::MouseEntered) {
            if (music_paused) music.play();
            awake();
        }

        else if (event.type == sf::Event::TouchBegan) {
            ns_LOG("TouchEvent : finger =", event.touch.finger, " ; position = (", event.touch.x, ",", event.touch.y, ")");
            ns::android::vibrate(75);
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
    ns::Res::load("");  // load root assets folder

    Game g;
    g.run();
}
