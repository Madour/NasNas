/**
* Created by Modar Nasser on 10/11/2020.
**/

#pragma once

#include <string>

namespace ns::utils {

    namespace path {
        auto getFilename(const std::string& path) -> std::string;
        auto getStem(const std::string& path) -> std::string;
        auto getExtension(const std::string& path) -> std::string;
        auto getPath(const std::string& path) -> std::string;
        void removeFilename(std::string& path);
    }
}
