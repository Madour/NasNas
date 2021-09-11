// Created by Modar Nasser on 11/09/2021.

#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <typeindex>

#include <jni.h>
#include <android/native_activity.h>
#include <android/window.h>
#include <SFML/System/NativeActivity.hpp>


namespace ns::android {

    struct JClass;
    struct JMethodBase;

    class JniManager {
        std::unordered_map<std::string, jclass> m_jclass_cache;
        std::unordered_map<std::string, jmethodID> m_jmethodID_cache;
        std::unordered_map<std::type_index, JClass*> m_classes;

        JNIEnv* m_env;

    public:
        void init();
        auto env() const -> JNIEnv*;

        template <typename T, typename = std::enable_if<std::is_base_of_v<JClass, T>>>
        void registerClass();

        template <typename T>
        auto get(jobject object) -> T&;

        auto getMethodID(JMethodBase* method) const -> jmethodID;

        void attachThread();

        void detachThread();

    private:
        void initCaches();

        template <typename Class, typename Method>
        void fillMethodIDCache();
    };

    template <typename T, typename En>
    void JniManager::registerClass() {
        auto* instance = new T();

        // cache the jclass
        m_jclass_cache[instance->name] = m_env->FindClass(instance->name);

        // cache class methods
        for (auto* method : instance->methods) {
            m_jmethodID_cache[method->fullname] = m_env->GetMethodID(m_jclass_cache[instance->name], method->name, method->sig);
        }

        // store the instance
        auto index = std::type_index(typeid(T));
        m_classes[index] = instance;
    }

    template <typename T>
    auto JniManager::get(jobject object) -> T& {
        auto index = std::type_index(typeid(T));
        auto* instance = static_cast<T*>(m_classes.at(index));
        instance->current_object = object;
        return *instance;
    }

    extern JniManager JNI;
}
