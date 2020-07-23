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
        static auto getName() -> const std::string& ;
        static auto get() -> Dir&;
        static auto getTexture(const std::string& texture_path) -> sf::Texture&;
        static auto getFont(const std::string& font_path) -> sf::Font&;
        static void printTree();

    private:
        static Dir* m_data;
        static bool m_ready;
        static std::string m_root_dir;

        ResourceManager();
        ~ResourceManager();
        static void checkReady();
    };

    typedef ResourceManager Res;
}
