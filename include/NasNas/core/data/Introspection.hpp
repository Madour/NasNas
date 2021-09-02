// Created by Modar Nasser on 30/07/2021.

#pragma once

#include "NasNas/core/data/Rect.hpp"

namespace introspect {
    using namespace std;
#define NS_DEFINE_HAS_METHOD(name, signature)                                   \
    template<typename, typename T=signature>                                    \
    struct has_##name {};                                                       \
    template<typename C, typename Ret, typename... Args>                        \
    struct has_##name<C, Ret(Args...)> {                                        \
    private:                                                                    \
        template <typename Rt>                                                  \
        using remove_const_ref = remove_const_t<remove_reference_t<Rt>>;        \
        template<typename T>                                                    \
        static constexpr auto check(T*) ->                                      \
            enable_if_t<is_base_of_v<                                           \
                remove_const_ref<decltype(declval<T>().name(declval<Args>()...))>,\
                remove_const_ref<Ret>                                           \
            >, true_type>;                                                      \
        template<typename> static constexpr false_type check(...);              \
        using type = decltype(check<C>(0));                                     \
    public:                                                                     \
        static constexpr bool value = type::value;                              \
    };                                                                          \
    template <typename C, typename T=signature>                                 \
    inline constexpr bool has_##name##_v = has_##name<C, T>::value

    NS_DEFINE_HAS_METHOD(getPosition, sf::Vector2f());
    NS_DEFINE_HAS_METHOD(getGlobalBounds, ns::FloatRect());
    NS_DEFINE_HAS_METHOD(getBounds, ns::FloatRect());
    NS_DEFINE_HAS_METHOD(update, void());
}
