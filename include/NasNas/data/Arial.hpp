/**
* Created by Modar Nasser on 28/06/2020.
**/


#pragma once

#include <SFML/Graphics.hpp>

namespace ns {

    class Arial {
    public:
        static auto getFont() -> sf::Font&;

    private:
        static const unsigned char data[] ;
        static const unsigned int len;

        explicit Arial();
        sf::Font m_font;
    };

}
