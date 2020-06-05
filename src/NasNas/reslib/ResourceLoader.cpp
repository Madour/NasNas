/**
* Created by Modar Nasser on 23/04/2020.
**/

#include "NasNas/reslib/ResourceLoader.hpp"
using namespace ns;


Dir::Dir(const std::string &name) {
    this->name = name;
}

Dir::~Dir() = default;

void Dir::load(const std::filesystem::path& path) {
    namespace fs = std::filesystem;
    if (fs::is_directory(fs::status(path))) {
        for (const auto& file: fs::directory_iterator(path)) {
            if (fs::is_regular_file(file)) {
                if (file.path().has_extension()) {
                    if (this->texture_extensions.count(file.path().extension().string()) != 0) {
                        std::shared_ptr<sf::Texture> new_texture(new sf::Texture());
                        new_texture->loadFromFile(file.path().string());
                        this->textures[file.path().stem().string()] = new_texture;
                    }
                    else if (this->fonts_extensions.count(file.path().extension().string()) != 0) {
                        std::shared_ptr<sf::Font> new_font(new sf::Font());
                        new_font->loadFromFile(file.path().string());
                        this->fonts[file.path().stem().string()] = new_font;
                    }
                }
            }
            else if (fs::is_directory(file)) {
                std::shared_ptr<Dir> new_dir(new Dir(file.path().filename().string()));
                this->dirs[file.path().filename().string()] = new_dir;
                new_dir->load(file.path());

            }
        }
    }
    else {
        std::cout << "ResourceLoader Exception : Path "<<path.string()<<" does not exist."<< std::endl;
        throw std::exception();
    }
}

auto Dir::in(const std::string &dir_name) -> Dir& {
    return *this->dirs.at(dir_name).get();
}

auto Dir::getName() -> const std::string& {
    return this->name;
}


auto Dir::getTexture(const std::string& texture_name) -> sf::Texture&{
    return *this->textures.at(texture_name).get();
}

auto Dir::getFont(const std::string& font_name) -> sf::Font& {
    return *this->fonts.at(font_name).get();
}


void Dir::print_tree(int indent) {
    auto print_indent = [](int n) { for (int i = 0; i < n; ++i) { std::cout << "|  "; } };

    for(auto& item: this->dirs) {
        print_indent(indent);
        std::cout << "|_ " << item.first << " : Dir" << std::endl;
        item.second->print_tree(indent + 1);
    }

    for(auto& item: this->textures) {
        print_indent(indent);
        std::cout<< "|_ " << item.first << " : Texture" << std::endl;
    }
    for(auto& item: this->fonts) {
        print_indent(indent);
        std::cout<< "|_ " << item.first << " : Font" << std::endl;
    }
}

