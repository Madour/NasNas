// Created by Modar Nasser on 11/09/2021.

#pragma once

#ifndef __ANDROID__
#error "NasNas Android Activity header can only be used when developing for Android platform"
#endif

#include <string>
#include <android/native_activity.h>

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
