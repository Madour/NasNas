/**
* Created by Modar Nasser on 23/04/2020.
**/


#pragma once

#include <memory>
#include <set>
#include <string>
#include <unordered_map>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ns {

    class Dir {
    public:
        Dir(std::string  name, Dir* parent);
        ~Dir();
        void load(const std::string& path, bool autoload);
        auto in(const std::string& dir_name) -> Dir&;
        auto getName() -> const std::string&;
        auto getPath() -> std::string;
        auto getTexture(const std::string& texture_name) -> sf::Texture&;
        auto getFont(const std::string& font_name) -> sf::Font&;
        void printTree(int indent=0);

    private:
        static const std::set<std::string> texture_extensions;
        static const std::set<std::string> fonts_extensions;

        Dir* m_parent;
        std::string m_name;
        std::unordered_map<std::string, std::unique_ptr<Dir>> m_dirs;
        std::unordered_map<std::string, std::unique_ptr<sf::Texture>> m_textures;
        std::unordered_map<std::string, std::unique_ptr<sf::Font>> m_fonts;
    };

}
