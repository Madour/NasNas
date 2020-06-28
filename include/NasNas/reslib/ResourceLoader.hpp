/**
* Created by Modar Nasser on 23/04/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <set>

namespace ns {

    class ResourceManager;

    class Dir {

    using t_DirsMap = std::unordered_map<std::string, std::shared_ptr<Dir>>;
    using t_TexturesMap = std::unordered_map<std::string, std::shared_ptr<sf::Texture>>;
    using t_FontsMap = std::unordered_map<std::string, std::shared_ptr<sf::Font>>;

    public:
        explicit Dir(const std::string& name);
        ~Dir();
        void load(const std::filesystem::path& path);
        void print_tree(int indent=0);
        auto in(const std::string& dir_name) -> Dir&;
        auto getName() -> const std::string&;
        auto getTexture(const std::string& texture_name) -> sf::Texture&;
        auto getFont(const std::string& font_name) -> sf::Font&;

    private:
        const static std::set<std::string> texture_extensions;
        const static std::set<std::string> fonts_extensions;

        std::string m_name;
        t_DirsMap m_dirs;
        t_TexturesMap m_textures;
        t_FontsMap m_fonts;
    };

}
