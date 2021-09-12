// Created by Modar Nasser on 11/09/2021.

#pragma once

#include "JavaWrapper.hpp"

namespace ns::android {

    namespace app {
        struct NativeActivity : JClass {
            NativeActivity() :
            JClass("android/app/NativeActivity"),
            setRequestedOrientation(this, "setRequestedOrientation", "(I)V"),
            getSystemService(this, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;"),
            getWindow(this, "getWindow", "()Landroid/view/Window;")
            {}

            JMethod<void(jint)> setRequestedOrientation;
            JMethod<jobject(jobject)> getSystemService;
            JMethod<jobject()> getWindow;
        };
    }

    namespace content {
        struct Context : JClass {
            Context() :
            JClass("android/content/Context"),
            VIBRATOR_SERVICE(this, "VIBRATOR_SERVICE", "Ljava/lang/String;")
            {}

            JStaticField<jobject> VIBRATOR_SERVICE;
        };
    }

    namespace os {
        struct Vibrator : JClass {
            Vibrator() :
            JClass("android/os/Vibrator"),
            vibrate(this, "vibrate", "(J)V")
            {}

            JMethod<void(jlong)> vibrate;
        };
    }

    namespace view {
        struct View : JClass {
            View() :
            JClass("android/view/View"),
            setSystemUiVisibility(this, "setSystemUiVisibility", "(I)V")
            {}

            JMethod<void(jint)> setSystemUiVisibility;
        };

        struct Window : JClass {
            Window() :
            JClass("android/view/Window"),
            getDecorView(this, "getDecorView", "()Landroid/view/View;")
            {}

            JMethod<jobject()> getDecorView;
        };
    }

}
