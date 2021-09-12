// Created by Modar Nasser on 11/09/2021.

#pragma once

#include <string>
#include <SFML/System/NativeActivity.hpp>

namespace ns::android {

    void init();

    auto getActivity() -> ANativeActivity*;

    void hideStatusBar();
    void hideNavigation();

    enum ScreenOrientation {
        Landscape,
        Portrait
    };
    void setScreenOrientation(ScreenOrientation orientation);

    void vibrate(int milliseconds);

    void showToast(const std::string& text);
}
