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

#include "NasNas/core/android/Activity.hpp"
#include "JniManager.hpp"
#include "JavaWrapper.hpp"
#include "JavaClasses.hpp"

using namespace ns;
using namespace ns::android;

android::JniManager android::JNI;

void JniManager::init() {
    attachThread();
    initCaches();
}

JniManager::~JniManager() {
    for (auto& item : m_classes)
        delete item.second;
    for (auto& item : m_jclass_cache)
        m_env->DeleteGlobalRef(item.second);
    detachThread();
}

auto JniManager::env() const -> JNIEnv* {
    return m_env;
}

void JniManager::initCaches() {
    registerClass<android::app::NativeActivity>();
    registerClass<android::content::Context>();
    registerClass<android::os::Vibrator>();
    registerClass<android::view::View>();
    registerClass<android::view::Window>();
    registerClass<android::widget::Toast>();
}

auto JniManager::getClass(JClass* cls) const -> jclass {
    return m_jclass_cache.at(cls->name);
}
auto JniManager::getMethodID(JClassMember* method) const -> jmethodID {
    return m_jmethodID_cache.at(method->fullname);
}
auto JniManager::getFieldID(JClassMember* field) const -> jfieldID {
    return m_jfieldID_cache.at(field->fullname);
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
