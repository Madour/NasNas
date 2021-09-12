// Created by Modar Nasser on 11/09/2021.


#include "NasNas/core/android/Activity.hpp"

#include "JniManager.hpp"
#include "JavaClasses.hpp"

using namespace ns;

void android::init() {
    JNI.init();
}

auto android::getActivity() -> ANativeActivity* {
    return sf::getNativeActivity();
}

void android::hideStatusBar() {
    ANativeActivity_setWindowFlags(getActivity(), AWINDOW_FLAG_FULLSCREEN, 0);
}

void android::hideNavigation() {
    auto* activity = getActivity();
    JNI.attachThread();

    auto object_Window = JNI.get<android::app::NativeActivity>(activity->clazz).getWindow();
    auto object_View = JNI.get<android::view::Window>(object_Window).getDecorView();

    jint SYSTEM_UI_FLAG_HIDE_NAVIGATION = 0x2;
    JNI.get<android::view::View>(object_View).setSystemUiVisibility(SYSTEM_UI_FLAG_HIDE_NAVIGATION);

    JNI.env()->DeleteLocalRef(object_View);
    JNI.env()->DeleteLocalRef(object_Window);

    JNI.detachThread();
}

void android::setScreenOrientation(ScreenOrientation orientation) {
    auto* activity = getActivity();
    JNI.attachThread();

    JNI.get<android::app::NativeActivity>(activity->clazz).setRequestedOrientation(static_cast<jint>(orientation));

    JNI.detachThread();
}

void android::vibrate(int milliseconds) {
    auto* activity = getActivity();
    JNI.attachThread();

    auto vibrator_service_str = JNI.get<android::content::Context>().VIBRATOR_SERVICE.val();
    auto object_Vibrator = JNI.get<android::app::NativeActivity>(activity->clazz).getSystemService(vibrator_service_str);
    JNI.get<android::os::Vibrator>(object_Vibrator).vibrate(milliseconds);

    JNI.env()->DeleteLocalRef(vibrator_service_str);
    JNI.env()->DeleteLocalRef(object_Vibrator);

    JNI.detachThread();
}
