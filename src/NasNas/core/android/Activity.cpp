// Created by Modar Nasser on 11/09/2021.


#include "NasNas/core/android/Activity.hpp"
#include "Jni.hpp"

using namespace ns;


android::JniManager JNI;


void android::init() {
    JNI.init();
    //android::hideNavigation();
}

void android::hideStatusBar() {
    // hide status bar
    ANativeActivity_setWindowFlags(JNI.getActivity(), AWINDOW_FLAG_FULLSCREEN, 0);
}

void android::hideNavigation() {
    auto* activity = JNI.getActivity();

    JNI.attachThread();

    auto object_Window = JNI.env()->CallObjectMethod(activity->clazz, JNI.getMethodID(app::NativeActivity::getWindow::name));
    auto object_DecorView = JNI.env()->CallObjectMethod(object_Window, JNI.getMethodID(view::Window::getDecorView::name));

    jint SYSTEM_UI_FLAG_HIDE_NAVIGATION = 0x2;
    JNI.env()->CallVoidMethod(object_DecorView, JNI.getMethodID(view::View::setSystemUiVisibility::name), SYSTEM_UI_FLAG_HIDE_NAVIGATION);

    JNI.env()->DeleteLocalRef(object_DecorView);
    JNI.env()->DeleteLocalRef(object_Window);

    JNI.detachThread();
}

void android::setScreenOrientation(ScreenOrientation orientation) {
    auto* activity = JNI.getActivity();

    JNI.attachThread();

    JNI.env()->CallVoidMethod(activity->clazz, JNI.getMethodID(app::NativeActivity::setRequestedOrientation::name), static_cast<jint>(orientation));

    JNI.detachThread();
}
