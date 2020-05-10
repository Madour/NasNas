/**
* Created by Modar Nasser on 23/04/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <filesystem>
#include <set>

#include "NasNas/core/Logger.hpp"

namespace ns {
    class ResourceManager;

    class Dir {

    using DirsMap = std::unordered_map<std::string, std::shared_ptr<Dir>>;
    using TexturesMap = std::unordered_map<std::string, std::shared_ptr<sf::Texture>>;
    using FontsMap = std::unordered_map<std::string, std::shared_ptr<sf::Font>>;
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
        std::string name;
        DirsMap dirs;
        TexturesMap textures;
        FontsMap fonts;

        const std::set<std::string> texture_extensions = {".png", ".jpg", ".bmp"};
        const std::set<std::string> fonts_extensions = {".ttf"};
    };

}
