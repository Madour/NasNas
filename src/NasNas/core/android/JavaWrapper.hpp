// Created by Modar Nasser on 11/09/2021.

#pragma once

#include <vector>
#include <typeindex>
#include <functional>
#include <unordered_map>

#include "NasNas/core/data/Singleton.hpp"
#include "JniManager.hpp"

namespace ns::android {

    struct JMethodBase;

    struct JClass {
        explicit JClass(const char* pname);
        auto object() -> jobject;

        const char* name;
        std::vector<const JMethodBase*> methods;

    private:
        friend JniManager;
        jobject current_object;
    };

    struct JMethodBase {
        JMethodBase(JClass* pcls, const char* pname, const char* psig);

        JClass* cls;
        const char* name;
        const char* sig;
        std::string fullname;
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
        }
    };

}
