// Created by Modar Nasser on 11/09/2021.

#pragma once

namespace ns::android {

    void init();

    void hideStatusBar();
    void hideNavigation();

    void vibrate(int milliseconds);

    enum class ScreenOrientation {
        Landscape,
        Portrait
    };
    void setScreenOrientation(ScreenOrientation orientation);
}
