/**
* Created by Modar Nasser on 15/04/2020.
**/

#pragma once

#include <type_traits>

namespace ns {
    // forward declaration of App type
    class App;

    namespace detail {
        class AppComponent {
        public:
            static App* app;
        };
    }

    /** AppAccess
     * Allows any class to access App properties
     */
    template <typename T=App, typename = std::enable_if<std::is_base_of_v<App, T>>>
    class AppAccess : protected detail::AppComponent {
    public:
        static constexpr auto app() -> T& {
            if constexpr(std::is_same_v<App, T>)
                return *AppComponent::app;
            return *static_cast<T*>(AppComponent::app);
        }
    };

}
