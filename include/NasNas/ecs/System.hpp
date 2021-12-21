// Created by Modar Nasser on 16/08/2021.

#pragma once

#include <functional>
#include <utility>

namespace ns::ecs {
    namespace detail {
        template <typename T>
        class Registry;
    }

    template <typename... TComps>
    class System {
        friend detail::Registry<unsigned long>;
        using FunctionType = std::function<void(TComps&...)>;
    public:
        System() = default;

        explicit System(FunctionType fn) {
            set(fn);
        }

        auto operator=(FunctionType fn) -> System<TComps...>& {
            set(fn);
            return *this;
        }

        void operator() (TComps&... comps) {
            m_function(comps...);
        }

    private:
        void set(FunctionType fn) {
            m_function = std::move(fn);
        }

        FunctionType m_function {};
    };
}
