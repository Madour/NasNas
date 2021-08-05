/**
* Created by Modar Nasser on 23/04/2020.
**/


#pragma once

#include "NasNas/reslib/ResourceLoader.hpp"

namespace ns {

    class ResourceManager {
    public:
        static auto load(const std::string& assets_directory_name, bool autoload=true) -> bool;
        static void dispose();
        static auto in(const std::string& dir_name) -> Dir&;

        static auto getName() -> const std::string& ;
        static auto getTexture(const std::string& texture_path) -> sf::Texture&;
        static auto getFont(const std::string& font_path) -> sf::Font&;
        static void printTree();

    private:
        static Dir* m_data;
        static bool m_ready;
        static std::string m_root_dir_name;

        ResourceManager();
        ~ResourceManager();
        static void checkReady();
        static auto resolvePath(const std::string& p) -> std::pair<Dir*, std::string>;
    };

    typedef ResourceManager Res;
}
