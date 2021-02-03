/**
* Created by Modar Nasser on 10/11/2020.
**/

#pragma once

#include <string>
#include <functional>

namespace ns::utils {

    namespace path {
        auto getFilename(const std::string& path) -> std::string;
        auto getStem(const std::string& path) -> std::string;
        auto getExtension(const std::string& path) -> std::string;
        auto getPath(const std::string& path) -> std::string;
        void removeFilename(std::string& path);
    }

    struct bool_switch {
        bool_switch(std::function<void()>  on_true, std::function<void()>  on_false);
        virtual auto operator=(bool value) -> bool;
        virtual explicit operator bool() const;
    private:
        bool m_val;
        std::function<void()> m_on_true;
        std::function<void()> m_on_false;

    };
}
