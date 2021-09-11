// Created by Modar Nasser on 11/09/2021.

#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <jni.h>
#include <android/native_activity.h>
#include <android/window.h>
#include <SFML/System/NativeActivity.hpp>

namespace ns::android {

    struct app {
        struct NativeActivity {
            static constexpr auto name = "android/app/NativeActivity";
            struct getSystemService {
                static constexpr auto name = "getSystemService";
                static constexpr auto sig = "(Ljava/lang/String;)Ljava/lang/Object;";
            };
            struct getWindow {
                static constexpr auto name = "getWindow";
                static constexpr auto sig = "()Landroid/view/Window;";
            };
            struct setRequestedOrientation {
                static constexpr auto name = "setRequestedOrientation";
                static constexpr auto sig = "(I)V";
            };
        };
    };

    struct content {
        struct Context {
            static constexpr auto name = "android/content/Context";
        };
    };
    struct view {
        struct View {
            static constexpr auto name = "android/view/View";
            struct setSystemUiVisibility {
                static constexpr auto name = "setSystemUiVisibility";
                static constexpr auto sig = "(I)V";
            };
        };
        struct Window {
            static constexpr auto name = "android/view/Window";
            struct getDecorView {
                static constexpr auto name = "getDecorView";
                static constexpr auto sig = "()Landroid/view/View;";
            };
        };
    };

    class JniManager {
        JNIEnv* m_env;
        std::unordered_map<std::string, jclass> m_jclass_cache;
        std::unordered_map<std::string, jmethodID> m_jmethodID_cache;

    public:
        auto getActivity() -> ANativeActivity*;
        void init();
        auto env() const -> JNIEnv*;
        auto getClass(const char* name) const -> jclass;
        auto getMethodID(const char* name) const -> jmethodID;

        void attachThread();

        void detachThread();

    private:
        void initCaches();

        template <typename Class, typename Method>
        void fillMethodIDCache();
    };

    template <typename Class, typename Method>
    void JniManager::fillMethodIDCache() {
        std::string full_name = std::string(Class::name) + "/" + std::string(Method::name);
        m_jmethodID_cache[Method::name] = m_env->GetMethodID(m_jclass_cache[Class::name], Method::name, Method::sig);
    }

}
