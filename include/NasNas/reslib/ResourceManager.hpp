/**
* Created by Modar Nasser on 23/04/2020.
**/

#pragma once

#include "NasNas/reslib/ResourceLoader.hpp"

namespace ns {

    class ResourceManager {
    public:
        static auto load(const std::string& assets_directory_name) -> bool;
        static void dispose();
        static auto get() -> Dir&;
        static void printTree();
    private:
        ResourceManager();
        ~ResourceManager();
        static Dir* data;
        static bool ready;
    };

    typedef ResourceManager Res;
}
