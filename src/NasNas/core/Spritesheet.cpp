/**
* Created by Modar Nasser on 25/04/2020.
**/


#include "NasNas/core/Spritesheet.hpp"

#include <utility>

using namespace ns;

Spritesheet::Spritesheet(std::string name, const sf::Texture& texture) :
name(std::move(name)),
texture(&texture)
{}

Spritesheet::Spritesheet(std::string  name, const sf::Texture& texture, const std::vector<Anim*>& anims) :
Spritesheet(std::move(name), texture) {
    for(const auto& anim: anims) {
        m_anims_map[anim->getName()] = anim;
    }
}

Spritesheet::~Spritesheet() {
    for(auto& [anim_name, anim]: m_anims_map) {
        delete(anim);
    }
}

void Spritesheet::setGrid(const sf::Vector2i& cell_size, int columns_nb, int margin, int spacing) {
    m_cell_size = cell_size;
    if (columns_nb <= 0) {
        std::cout << "Error (Spritesheet::setGrid) : Columns number in Spritesheet " << name << " must be superior or equal to 1.";
        exit(-1);
    }
    m_columns = columns_nb;
    m_margin = margin;
    m_spacing = spacing;
}

void Spritesheet::addAnim(Anim* new_anim) {
    m_anims_map[new_anim->getName()] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, int first_frame, int nb_of_frames,
                            const std::variant<int, std::vector<int>>& duration,
                            const std::variant<sf::Vector2i, std::vector<sf::Vector2i>>& origin) {
    if (!std::holds_alternative<int>(duration) && std::get<std::vector<int>>(duration).size() < nb_of_frames) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching for durations vector in Anim "
                    << anim_name << "." << std::endl;
        exit(-1);
    }
    if (!std::holds_alternative<sf::Vector2i>(origin) && std::get<std::vector<sf::Vector2i>>(origin).size() < nb_of_frames) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching for origins vector in Anim "
                    << anim_name << "." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (int i = 0; i < nb_of_frames; ++i) {
        auto x = ((i+first_frame) % m_columns)*(m_cell_size.x + m_spacing) + m_margin;
        auto y = ((i+first_frame) / m_columns)*(m_cell_size.y + m_spacing) + m_margin;
        int f_duration = std::holds_alternative<int>(duration) ?
                std::get<int>(duration) : std::get<std::vector<int>>(duration)[i];
        sf::Vector2i f_origin = std::holds_alternative<sf::Vector2i>(origin) ?
                std::get<sf::Vector2i>(origin) : std::get<std::vector<sf::Vector2i>>(origin)[i];;
        new_anim->add(AnimFrame({{x, y}, m_cell_size}, f_duration, f_origin));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, const std::vector<int>& frames,
                          const std::variant<int, std::vector<int>>& duration,
                          const std::variant<sf::Vector2i, std::vector<sf::Vector2i>>& origin) {
    if (!std::holds_alternative<int>(duration) && std::get<std::vector<int>>(duration).size() < frames.size()) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching for durations vector in Anim "
                  << anim_name << "." << std::endl;
        exit(-1);
    }
    if (!std::holds_alternative<sf::Vector2i>(origin) && std::get<std::vector<sf::Vector2i>>(origin).size() < frames.size()) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching for origins vector in Anim "
                  << anim_name << "." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (int i = 0; i < frames.size(); ++i) {
        auto x = (frames[i] % m_columns)*(m_cell_size.x + m_spacing) + m_margin;
        auto y = (frames[i] / m_columns)*(m_cell_size.y + m_spacing) + m_margin;
        int f_duration = std::holds_alternative<int>(duration) ?
                         std::get<int>(duration) : std::get<std::vector<int>>(duration)[i];
        sf::Vector2i f_origin = std::holds_alternative<sf::Vector2i>(origin) ?
                                std::get<sf::Vector2i>(origin) : std::get<std::vector<sf::Vector2i>>(origin)[i];;
        new_anim->add(AnimFrame({{x, y}, m_cell_size}, f_duration, f_origin));
    }
    m_anims_map[anim_name] = new_anim;
}

auto Spritesheet::getAnimsMap() -> const std::unordered_map<std::string, Anim*>& {
    return m_anims_map;
}

auto Spritesheet::getAnim(const std::string& anim_name) -> const Anim& {
    if(m_anims_map.count(anim_name) > 0)
        return *m_anims_map.at(anim_name);
    else
        throw std::invalid_argument("Error (Spritesheet::getAnim) : Accessing unexisting Anim "+anim_name+" in spritesheet "+name);
}
