/**
* Created by Modar Nasser on 23/04/2020.
**/

#include <NasNas/reslib/ResourceLoader.hpp>

#include <iostream>
#ifndef __ANDROID__
#include <filesystem>
#else
#include <NasNas/core/android/Activity.hpp>
#include <NasNas/core/data/Utils.hpp>
#include "../core/android/JniManager.hpp"
#include "../core/android/JavaClasses.hpp"
#endif

using namespace ns;

const std::set<std::string> Dir::texture_extensions = {".png", ".jpg", ".bmp"};
const std::set<std::string> Dir::fonts_extensions = {".ttf"};

Dir::Dir(std::string name, Dir* parent) :
m_name(std::move(name)),
m_parent(parent)
{}

Dir::~Dir() = default;

void Dir::load(const std::string& path, bool autoload) {
#ifndef __ANDROID__
    namespace fs = std::filesystem;
    if (fs::is_directory(fs::status(path))) {
        for (const auto& file : fs::directory_iterator(path)) {
            auto filename = file.path().filename().string();
            if (fs::is_regular_file(file)) {
                if (file.path().has_extension()) {
                    if (Dir::texture_extensions.count(file.path().extension().string()) != 0) {
                        m_textures.emplace(filename, nullptr);
                        if (autoload) {
                            std::unique_ptr<sf::Texture> new_texture(new sf::Texture());
                            new_texture->loadFromFile(file.path().string());
                            m_textures[filename] = std::move(new_texture);
                        }
                    }
                    else if (Dir::fonts_extensions.count(file.path().extension().string()) != 0) {
                        m_fonts.emplace(filename, nullptr);
                        if (autoload) {
                            std::unique_ptr<sf::Font> new_font(new sf::Font());
                            new_font->loadFromFile(file.path().string());
                            m_fonts[filename] = std::move(new_font);
                        }
                    }
                }
            }
            else if (fs::is_directory(file)) {
                std::unique_ptr<Dir> new_dir(new Dir(filename, this));
                m_dirs[filename] = std::move(new_dir);
                m_dirs[filename]->load(file.path().string(), autoload);
            }
        }
    }
    else {
        std::cout << "ResourceLoader Exception : Path "<<path<<" does not exist."<< std::endl;
        throw std::exception();
    }
#else
    using namespace android;
    auto* activity = getActivity();
    auto object_asset_manager = JNI.get<app::NativeActivity>(activity->clazz).getAssets();
    auto jstring_path = JNI.env()->NewStringUTF(path.c_str());
    auto array_files = JNI.get<content::res::AssetManager>(object_asset_manager).list(jstring_path);
    for (int i = 0; i < JNI.env()->GetArrayLength(array_files); ++i) {
        auto object_file_name = static_cast<jstring>(JNI.env()->GetObjectArrayElement(array_files, i));
        auto file_name = std::string(JNI.env()->GetStringUTFChars(object_file_name, nullptr));
        auto file_path = (path.empty() ? "" : path + "/") + file_name;
        auto jstring_file_path = JNI.env()->NewStringUTF(file_path.c_str());
        auto file_is_folder = JNI.env()->GetArrayLength(JNI.get<content::res::AssetManager>(object_asset_manager).list(jstring_file_path)) > 0;
        if (file_is_folder) {
            m_dirs[file_name] = std::make_unique<Dir>(file_name, this);
            m_dirs[file_name]->load(file_path, autoload);
        }
        else {
            auto extension = ns::utils::path::getExtension(file_name);
            if (Dir::texture_extensions.count(extension) != 0) {
                m_textures.emplace(file_name, nullptr);
                if (autoload) {
                    m_textures[file_name] = std::make_unique<sf::Texture>();
                    m_textures[file_name]->loadFromFile(file_path);
                }
            }
            else if (Dir::fonts_extensions.count(extension) != 0) {
                m_fonts.emplace(file_name, nullptr);
                if (autoload) {
                    m_fonts[file_name] = std::make_unique<sf::Font>();
                    m_fonts[file_name]->loadFromFile(file_path);
                }
            }
        }
    }
#endif
}

auto Dir::in(const std::string& dir_name) -> Dir& {
    if (dir_name == "..") {
        if (m_parent)
            return *m_parent;
        else {
            std::cerr << "Directory «" << m_name << "» does not have parent directory." << std::endl;
            exit(-1);
        }
    }
    if (m_dirs.count(dir_name) > 0)
        return *m_dirs.at(dir_name);

    std::cerr << "Directory «" << m_name << "» does not contain a directory named " << "«" << dir_name << "».\n";
    exit(-1);
}

auto Dir::getName() -> const std::string& {
    return m_name;
}

auto Dir::getPath() -> std::string {
    std::string path = m_name;
    Dir* current_dir = this;
    while (current_dir->m_parent != nullptr) {
        current_dir = current_dir->m_parent;
        path = current_dir->m_name + "/" + path;
    }
    return path;
}

auto Dir::getTexture(const std::string& texture_name) -> sf::Texture& {
    if (m_textures.find(texture_name) != m_textures.end()) {
        auto& ptr = m_textures.at(texture_name);
        if (ptr == nullptr) {
            m_textures[texture_name] = std::make_unique<sf::Texture>();
            m_textures.at(texture_name)->loadFromFile(getPath()+"/"+texture_name);
        }
        return *m_textures.at(texture_name);
    }

    std::cerr << "Directory «" << getPath() << "» does not have a file named " << texture_name << std::endl;
    std::exit(-1);
}

auto Dir::getFont(const std::string& font_name) -> sf::Font& {
    if (m_fonts.find(font_name) != m_fonts.end()) {
        auto& ptr = m_fonts.at(font_name);
        if (ptr == nullptr) {
            m_fonts[font_name] = std::make_unique<sf::Font>();
            m_fonts.at(font_name)->loadFromFile(getPath()+"/"+font_name);
        }
        return *m_fonts.at(font_name);
    }

    std::cout << "Directory «" << getPath() << "» does not have a file named " << font_name << std::endl;
    std::exit(-1);
}

void Dir::printTree(int indent) {
    auto print_indent = [](int n) { for (int i = 0; i < n; ++i) { std::cout << "|  "; } };

    for(auto& [dir_name, dir_ptr]: m_dirs) {
        print_indent(indent);
        std::cout << "|_ " << dir_name << " : Dir" << '\n';
        dir_ptr->printTree(indent + 1);
    }

    for(auto& [texture_name, _]: m_textures) {
        print_indent(indent);
        std::cout<< "|_ " << texture_name << " : Texture" << '\n';
    }

    for(auto& [font_name, _]: m_fonts) {
        print_indent(indent);
        std::cout<< "|_ " << font_name << " : Font" << '\n';
    }
}
