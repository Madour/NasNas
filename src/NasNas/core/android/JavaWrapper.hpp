// Created by Modar Nasser on 11/09/2021.

#pragma once

#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include <jni.h>

#include "JniManager.hpp"

namespace ns::android {

    struct JClass {
        explicit JClass(const char* name);
        auto object() -> jobject;

        const char* name;
        std::vector<const JMethodBase*> methods;
        std::vector<const JStaticMethodBase*> static_methods;
        std::vector<const JStaticFieldBase*> static_fields;

    private:
        friend JniManager;
        jobject current_object;
    };

    struct JClassMember {
        JClassMember(JClass* cls, const char* name);
        JClass* cls;
        const char* name;
        std::string fullname;
    };

    struct JMethodBase : JClassMember {
        JMethodBase(JClass* cls, const char* name, const char* sig);
        const char* sig;
    };

    template <typename T>
    struct JMethod {};

    template <typename Ret, typename... Args>
    struct JMethod<Ret(Args...)> : JMethodBase {
        using JMethodBase::JMethodBase;
        auto operator()(Args... args) -> Ret {
            if constexpr(std::is_same_v<Ret, void>) {
                JNI.env()->CallVoidMethod(cls->object(), JNI.getMethodID(this), std::forward<Args>(args)...);
            }
            else if constexpr(std::is_same_v<Ret, jobject>) {
                return JNI.env()->CallObjectMethod(cls->object(), JNI.getMethodID(this), std::forward<Args>(args)...);
            }
            else if constexpr(std::is_same_v<Ret, jobjectArray>) {
                return static_cast<jobjectArray>(JNI.env()->CallObjectMethod(cls->object(), JNI.getMethodID(this), std::forward<Args>(args)...));
            }

        }
    };

    struct JStaticMethodBase : JClassMember {
        JStaticMethodBase(JClass* cls, const char* name, const char* sig);
        const char* sig;
    };

    template <typename T>
    struct JStaticMethod {};

    template <typename Ret, typename... Args>
    struct JStaticMethod<Ret(Args...)> : JStaticMethodBase {
        using JStaticMethodBase::JStaticMethodBase;
        auto operator()(Args... args) -> Ret {
            if constexpr(std::is_same_v<Ret, void>) {
                JNI.env()->CallStaticVoidMethod(JNI.getClass(cls), JNI.getMethodID(this), std::forward<Args>(args)...);
            }
            else if constexpr(std::is_same_v<Ret, jobject>) {
                return JNI.env()->CallStaticObjectMethod(JNI.getClass(cls), JNI.getMethodID(this), std::forward<Args>(args)...);
            }
        }
    };

    struct JStaticFieldBase : JClassMember {
        JStaticFieldBase(JClass* cls, const char* name, const char* type);
        const char* type;
    };

    template <typename T>
    struct JStaticField : JStaticFieldBase {
        using JStaticFieldBase::JStaticFieldBase;

        auto val() -> T {
            if constexpr(std::is_same_v<T, jobject>) {
                return JNI.env()->GetStaticObjectField(JNI.getClass(cls), JNI.getFieldID(this));
            }
        }
    };

}
