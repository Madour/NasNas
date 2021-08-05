// Created by Modar Nasser on 04/08/2021.

#pragma once

namespace ns::detail {
    template <class T>
    class Singleton {
    protected:
        Singleton() = default;
    public:
        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;

        static auto get() -> T&;
    };

    template <class T>
    auto Singleton<T>::get() -> T& {
        static T instance;
        return instance;
    }
}