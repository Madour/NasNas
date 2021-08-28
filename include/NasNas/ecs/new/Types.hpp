// Created by Modar Nasser on 16/08/2021.
#pragma once

namespace ns::ecs {
    using Entity = unsigned long;

    template <typename... TComps>
    class System {
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

namespace ns::ecs::detail {
    using UID = unsigned long;
    UID get_next_id() {
        static UID counter = 0;
        return counter++;
    }

    template <class T>
    UID getTypeId() {
        static UID id = get_next_id();
        return id;
    }
}
