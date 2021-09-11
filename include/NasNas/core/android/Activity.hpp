// Created by Modar Nasser on 11/09/2021.

#pragma once

#include <SFML/System/NativeActivity.hpp>

namespace ns::android {

    void init();

    auto getActivity() -> ANativeActivity*;

    void hideStatusBar();
    void hideNavigation();

    void vibrate(int milliseconds);

    enum class ScreenOrientation {
        Landscape,
        Portrait
    };
    void setScreenOrientation(ScreenOrientation orientation);
}
