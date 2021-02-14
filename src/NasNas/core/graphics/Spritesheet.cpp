/**
* Created by Modar Nasser on 25/04/2020.
**/


#include "NasNas/core/graphics/Spritesheet.hpp"

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

void Spritesheet::addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, int duration, const sf::Vector2i& origin) {
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < nb_of_frames; ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(first_frame+i), m_cell_size}, duration, origin));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, int duration, const std::vector<sf::Vector2i>& origins) {
    if (origins.size() < nb_of_frames) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with origins vector." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < nb_of_frames; ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(first_frame+i), m_cell_size}, duration, origins[i]));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, const std::vector<int>& durations, const sf::Vector2i& origin) {
    if (durations.size() < nb_of_frames) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with durations vector." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < nb_of_frames; ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(first_frame+i), m_cell_size}, durations[i], origin));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, unsigned int first_frame, unsigned int nb_of_frames, const std::vector<int>& durations, const std::vector<sf::Vector2i>& origins) {
    if (origins.size() < nb_of_frames) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with origins vector." << std::endl;
        exit(-1);
    }
    if (durations.size() < nb_of_frames) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with durations vector." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < nb_of_frames; ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(first_frame+i), m_cell_size}, durations[i], origins [i]));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, int duration, const sf::Vector2i& origin) {
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < frames.size(); ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(frames[i]), m_cell_size}, duration, origin));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, int duration, const std::vector<sf::Vector2i>& origins) {
    if (origins.size() < frames.size()) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with origins vector." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < frames.size(); ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(frames[i]), m_cell_size}, duration, origins[i]));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, const std::vector<int>& durations, const sf::Vector2i& origin) {
    if (durations.size() < frames.size()) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with durations vector." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < frames.size(); ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(frames[i]), m_cell_size}, durations[i], origin));
    }
    m_anims_map[anim_name] = new_anim;
}

void Spritesheet::addAnim(const std::string& anim_name, const std::vector<unsigned int>& frames, const std::vector<int>& durations, const std::vector<sf::Vector2i>& origins) {
    if (origins.size() < frames.size()) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with origins vector." << std::endl;
        exit(-1);
    }
    if (durations.size() < frames.size()) {
        std::cout << "Error (Spritesheet::addAnim) : Number of frames not matching with durations vector." << std::endl;
        exit(-1);
    }
    auto* new_anim = new Anim(anim_name, {});
    for (unsigned int i = 0; i < frames.size(); ++i) {
        new_anim->add(AnimFrame({getFrameTexCoords(frames[i]), m_cell_size}, durations[i], origins[i]));
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

auto Spritesheet::getFrameTexCoords(unsigned int frame_index) const -> sf::Vector2i {
    return sf::Vector2i((frame_index % m_columns)*(m_cell_size.x + m_spacing) + m_margin,
                        (frame_index / m_columns)*(m_cell_size.y + m_spacing) + m_margin);
}
