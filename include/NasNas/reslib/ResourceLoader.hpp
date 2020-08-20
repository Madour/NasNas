/**
* Created by Modar Nasser on 23/04/2020.
**/


#pragma once

#include <set>
#include <iostream>
#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace ns {

    class ResourceManager;

    class Dir {
    public:
        Dir(std::string  name, Dir* parent);
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
        Dir* m_parent;
        std::unordered_map<std::string, std::unique_ptr<Dir>> m_dirs;
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
    };

}
