// Created by Modar Nasser on 11/09/2021.

#pragma once

#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <jni.h>

#include "JavaWrapperFwd.hpp"

namespace ns::android {

    class JniManager {
        std::unordered_map<std::string, jclass> m_jclass_cache;
        std::unordered_map<std::string, jmethodID> m_jmethodID_cache;
        std::unordered_map<std::string, jfieldID> m_jfieldID_cache;
        std::unordered_map<std::type_index, JClass*> m_classes;

        JNIEnv* m_env;

    public:
        ~JniManager();

        void init();
        auto env() const -> JNIEnv*;

        template <typename T, typename = std::enable_if<std::is_base_of_v<JClass, T>>>
        void registerClass();

        template <typename T>
        auto get(jobject object = nullptr) -> T&;

        auto getClass(JClass* cls) const -> jclass;
        auto getMethodID(JClassMember* method) const -> jmethodID;
        auto getFieldID(JClassMember* field) const -> jfieldID;

        void attachThread();
        void detachThread();

    private:
        void initCaches();
    };

    template <typename T, typename En>
    void JniManager::registerClass() {
        auto* instance = new T();

        // cache the jclass ref (after making it global to avoid "use of deleted local reference" error)
        auto class_ref = static_cast<jclass>(m_env->NewGlobalRef(m_env->FindClass(instance->name)));
        m_jclass_cache[instance->name] = class_ref;

        // cache class methods
        for (auto* method : instance->methods) {
            m_jmethodID_cache[method->fullname] = m_env->GetMethodID(class_ref, method->name, method->sig);
        }

        // cache class static fields
        for (auto* static_field : instance->static_fields) {
            m_jfieldID_cache[static_field->fullname] = m_env->GetStaticFieldID(class_ref, static_field->name, static_field->type);
        }

        // cache class static methods
        for (auto* static_method : instance->static_methods) {
            m_jmethodID_cache[static_method->fullname] = m_env->GetStaticMethodID(class_ref, static_method->name, static_method->sig);
        }

        // store the instance
        auto index = std::type_index(typeid(T));
        m_classes[index] = instance;
    }

    template <typename T>
    auto JniManager::get(jobject object) -> T& {
        auto index = std::type_index(typeid(T));
        auto* instance = static_cast<T*>(m_classes.at(index));
        if (object)
            instance->current_object = object;
        return *instance;
    }

    extern JniManager JNI;
}
