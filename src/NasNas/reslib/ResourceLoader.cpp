/**
* Created by Modar Nasser on 23/04/2020.
**/


#include <utility>
#include "NasNas/reslib/ResourceLoader.hpp"

using namespace ns;

const std::set<std::string> Dir::texture_extensions = {".png", ".jpg", ".bmp"};
const std::set<std::string> Dir::fonts_extensions = {".ttf"};

Dir::Dir(std::string  name, Dir* parent) :
m_name(std::move(name)),
m_parent(parent)
{}

Dir::~Dir() = default;

void Dir::load(const std::filesystem::path& path) {
    namespace fs = std::filesystem;
    if (fs::is_directory(fs::status(path))) {
        for (const auto& file: fs::directory_iterator(path)) {
            if (fs::is_regular_file(file)) {
                if (file.path().has_extension()) {
                    if (Dir::texture_extensions.count(file.path().extension().string()) != 0) {
                        std::unique_ptr<sf::Texture> new_texture(new sf::Texture());
                        new_texture->loadFromFile(file.path().string());
                        m_textures[file.path().filename().string()] = std::move(new_texture);
                    }
                    else if (Dir::fonts_extensions.count(file.path().extension().string()) != 0) {
                        std::unique_ptr<sf::Font> new_font(new sf::Font());
                        new_font->loadFromFile(file.path().string());
                        m_fonts[file.path().filename().string()] = std::move(new_font);
                    }
                }
            }
            else if (fs::is_directory(file)) {
                std::unique_ptr<Dir> new_dir(new Dir(file.path().filename().string(), this));
                m_dirs[file.path().filename().string()] = std::move(new_dir);
                m_dirs[file.path().filename().string()]->load(file.path());
            }
        }
    }
    else {
        std::cout << "ResourceLoader Exception : Path "<<path.string()<<" does not exist."<< std::endl;
        throw std::exception();
    }
}

auto Dir::in(const std::string& dir_name) -> Dir& {
    if (dir_name == "..") {
        if (m_parent)
            return *m_parent;
        else {
            std::cout << "Directory «" << m_name << "» does not have parent directory." << std::endl;
            exit(-1);
        }
    }
    if (m_dirs.count(dir_name) > 0)
        return *m_dirs.at(dir_name);

    std::cout << "Directory «" << m_name << "» does not contain a directory named " << "«" << dir_name << "».\n";
    exit(-1);
}

auto Dir::getName() -> const std::string& {
    return m_name;
}

auto Dir::getTexture(const std::string& texture_name) -> sf::Texture&{
    if (m_textures.count(texture_name) > 0)
        return *m_textures.at(texture_name);

    std::string path = m_name;
    Dir* current_dir = this;
    while (current_dir->m_parent != nullptr) {
        current_dir = current_dir->m_parent;
        path = current_dir->m_name + "/" + path;
    }
    std::cout << "Directory «" << path << "» does not have a file named " << texture_name << std::endl;
    std::exit(-1);
}

auto Dir::getFont(const std::string& font_name) -> sf::Font& {
    if (m_fonts.count(font_name) > 0)
        return *m_fonts.at(font_name);
    std::string path = m_name;
    Dir* current_dir = this;
    while (current_dir->m_parent != nullptr) {
        current_dir = current_dir->m_parent;
        path = current_dir->m_name + "/" + path;
    }
    std::cout << "Directory «" << path << "» does not have a file named " << font_name << std::endl;
    std::exit(-1);
}

void Dir::print_tree(int indent) {
    auto print_indent = [](int n) { for (int i = 0; i < n; ++i) { std::cout << "|  "; } };

    for(auto& [dir_name, dir_ptr]: m_dirs) {
        print_indent(indent);
        std::cout << "|_ " << dir_name << " : Dir" << std::endl;
        dir_ptr->print_tree(indent + 1);
    }

    for(auto& [texture_name, _]: m_textures) {
        print_indent(indent);
        std::cout<< "|_ " << texture_name << " : Texture" << std::endl;
    }

    for(auto& [font_name, _]: m_fonts) {
        print_indent(indent);
        std::cout<< "|_ " << font_name << " : Font" << std::endl;
    }
}
