/**
* Created by Modar Nasser on 07/01/2022.
**/

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

/**
 * This example shows how to draw Text and BitmapText
 */
class Game : public ns::App {
public:
    Game() : ns::App("Texts example", {720, 480}) {
        getWindow().setClearColor(sf::Color::White);

        auto* text = new sf::Text("Text using ttf font", ns::Arial::getFont());
        text->setFillColor(sf::Color::Black);
        text->setPosition(720/2 - text->getGlobalBounds().width/2,
                          480/2 - text->getGlobalBounds().height/2 - 50);

        auto* font = new ns::BitmapFont(
                ns::Res::getTexture("font.png"),
                {8, 8},
                " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;!?-+=",
                {{"ABCDEFGHIJKMNOPQRSTUVWXYZ?=-", 5}, {"fijl1", 3}},
                4
        );

        auto* bmp_text = new ns::BitmapText("Text using png font", font);
        bmp_text->scale(3.f, 3.f);
        bmp_text->setPosition(720/2 - bmp_text->getGlobalBounds().width/2,
                              480/2 - bmp_text->getGlobalBounds().height/2 + 50);

        auto& scene = createScene("main");
        auto& camera = createCamera("main", 0);
        camera.lookAt(scene);

        scene.getDefaultLayer().add(text);
        scene.getDefaultLayer().add(bmp_text);
    }
};

int main() {
    ns::Res::load("assets");

    Game g;
    g.run();

    ns::Res::dispose();
    return 0;
}
