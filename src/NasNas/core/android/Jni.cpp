// Created by Modar Nasser on 11/09/2021.

/*
 *
 * Java Types
 * V                         void
 * Z                         boolean
 * B                         byte
 * C                         char
 * S                         short
 * I                         int
 * J                         long
 * F                         float
 * D                         double
 * Lfully-qualified-class;   fully-qualified-class
 * [type                     type[]
 * (arg-types) ret-type      method type
 *
 */

#include <SFML/System/Err.hpp>
#include "Jni.hpp"

using namespace ns;
using namespace ns::android;

auto JniManager::getActivity() -> ANativeActivity* {
    return sf::getNativeActivity();
}

void JniManager::init() {
    initCaches();
}

auto JniManager::env() const -> JNIEnv* {
    return m_env;
}

void JniManager::initCaches() {
    attachThread();

    std::vector<const char*> class_names = {app::NativeActivity::name, content::Context::name, view::View::name, view::Window::name};

    for (auto& name : class_names) {
        m_jclass_cache[name] = m_env->FindClass(name);
    }

    fillMethodIDCache<app::NativeActivity, app::NativeActivity::getSystemService>();
    fillMethodIDCache<app::NativeActivity, app::NativeActivity::getWindow>();
    fillMethodIDCache<app::NativeActivity, app::NativeActivity::setRequestedOrientation>();

    fillMethodIDCache<view::Window, view::Window::getDecorView>();
    fillMethodIDCache<view::View, view::View::setSystemUiVisibility>();

    detachThread();
}

auto JniManager::getClass(const char* name) const -> jclass {
    return m_jclass_cache.at(name);
}

auto JniManager::getMethodID(const char* name) const -> jmethodID {
    return m_jmethodID_cache.at(name);
}

void JniManager::attachThread() {
    auto* activity = getActivity();
    auto* vm = activity->vm;
    m_env = activity->env;

    JavaVMAttachArgs attachargs;
    attachargs.version = JNI_VERSION_1_6;
    attachargs.name = "NativeThread";
    attachargs.group = NULL;
    vm->AttachCurrentThread(&m_env, &attachargs);
}

void JniManager::detachThread() {
    getActivity()->vm->DetachCurrentThread();
    m_env = getActivity()->env;
}
