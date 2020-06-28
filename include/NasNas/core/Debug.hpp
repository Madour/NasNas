/**
* Created by Modar Nasser on 01/05/2020.
**/

#pragma once

#include "SFML/Graphics.hpp"
#include "NasNas/reslib/ResourceManager.hpp"
#include "NasNas/ecs/BaseEntity.hpp"
#include <iostream>
#include <sstream>


namespace ns {
    auto operator<<(std::ostream& os, const sf::Vector2f& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector2i& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector2u& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector3f& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector3i& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::FloatRect& rect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::IntRect& rect) -> std::ostream&;

    class DebugTextInterface : public sf::Text {
    public:
        static sf::Color color;
        static sf::Color outline_color;
        static float outline_thickness;
        virtual void update() = 0;
    };

    template<typename T, typename  ObjT>
    class DebugText : public DebugTextInterface {
    public:
        DebugText(T *var_address, const std::string& label, const sf::Vector2f &position);

        DebugText(const T *var_address, const std::string& label, const sf::Vector2f &position);

        DebugText(
                ObjT* object_address,
                std::function<T(ObjT &)> method_address,
                const std::string& label,
                const sf::Vector2f& position
        );

        void update() override;

    private:
        DebugText(const std::string& label, const sf::Vector2f& position);

        std::string m_label;
        T* m_variable_address = nullptr;
        ObjT* m_object_address = nullptr;
        std::function<T(ObjT &)> m_method_address = nullptr;
    };

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(const std::string& label, const sf::Vector2f& position) {
        m_label = label;
        setFont(Res::getDefaultFont());
        setCharacterSize(20);
        setFillColor(ns::DebugTextInterface::color);
        setOutlineColor(ns::DebugTextInterface::outline_color);
        setOutlineThickness(ns::DebugTextInterface::outline_thickness);
        setPosition(position);
    }

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(T* var_address, const std::string& label, const sf::Vector2f &position)
            : DebugText(label, position) {
        m_variable_address = var_address;
    }

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(const T* var_address, const std::string& label, const sf::Vector2f &position)
            : DebugText(label, position) {
        m_variable_address = (T*) var_address;
    }

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(
            ObjT* object_address,
            std::function<T(ObjT &)> method_address,
            const std::string& label,
            const sf::Vector2f& position
    )
            : DebugText(label, position) {
        m_method_address = method_address;
        m_object_address = object_address;
    }
    template<typename T, typename ObjT>
    void DebugText<T, ObjT>::update() {
        std::ostringstream stream;
        stream << m_label << " ";
        if (m_variable_address != nullptr)
            stream << *m_variable_address;
        else
            stream << (m_method_address)(*m_object_address);

        setString(stream.str());
    }

}
