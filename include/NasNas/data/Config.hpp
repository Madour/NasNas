/**
* Created by Modar Nasser on 23/06/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"

namespace ns {

    class Config {
    public:
        static bool debug;
        class Window {
        public:
            static std::string title;
            static int width;
            static int height;
            static int view_width;
            static int view_height;
            static int style;
            static int framerate_limit;
            static int update_rate;
            static bool vertical_sync;
            static bool key_repeat;
            static bool cursor_visible;
            static bool cursor_grabbed;
        };
    };

}
