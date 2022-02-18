/**
* Created by Modar Nasser on 07/01/2022.
**/

#include <NasNas/Core.hpp>
#include <NasNas/Reslib.hpp>

/**
 * This example shows how to draw Text and BitmapText
 */
class Game : public ns::App {
    ns::BitmapFont bitmap_font;
public:
    Game() : ns::App("Texts example", {720, 480}) {
        getWindow().setClearColor(sf::Color::White);

        auto* text = new sf::Text(L"Text using ttf font ☻", ns::Arial::getFont());
        text->setFillColor(sf::Color::Black);
        text->setPosition(720/2 - text->getGlobalBounds().width/2,
                          480/2 - text->getGlobalBounds().height/2 - 85);

        bitmap_font.loadFromTexture(ns::Res::getTexture("font.png"), {8, 8}, 8);
        bitmap_font.setCharacters(L"_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklm"
                                  L"nopqrstuvwxyz0123456789.,:;!?-+=☺☻♥♦♣♠");
        bitmap_font.setCharactersAdvance({
            {L"fijlt.,:;", 3},
            {L" Tabcdeghknopqrsuvwxyz?+-=", 4},
            {L"_0123456789ABCDEFGHIJKLMNOPQRSUVXYZmw", 6},
            {L"W", 7},
        });

        auto* bmp_text = new ns::BitmapText(L"Text using png font ☻", bitmap_font);
        bmp_text->setColor(sf::Color::Black);
        bmp_text->scale(3.f, 3.f);
        bmp_text->setPosition(720/2 - bmp_text->getGlobalBounds().width/2,
                              480/2 - bmp_text->getGlobalBounds().height/2);

        auto* bmp_text2 = new ns::BitmapText(*bmp_text);
        bmp_text2->setLetterSpacing(1.4f);
        bmp_text2->setPosition(720/2 - bmp_text2->getGlobalBounds().width/2,
                              480/2 - bmp_text2->getGlobalBounds().height/2 + 75);

        auto& scene = createScene("main");
        auto& camera = createCamera("main", 0);
        camera.lookAt(scene);

        scene.getDefaultLayer().add(text);
        scene.getDefaultLayer().add(bmp_text);
        scene.getDefaultLayer().add(bmp_text2);
    }
};

int main() {
    ns::Res::load("assets");

    Game g;
    g.run();

    ns::Res::dispose();
    return 0;
}
