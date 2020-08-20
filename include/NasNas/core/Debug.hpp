/**
* Created by Modar Nasser on 01/05/2020.
**/


#pragma once

#include <iostream>
#include <sstream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <utility>
#include "NasNas/data/Arial.hpp"

namespace ns {

    /**
     * \brief Base class of all DebugText classes.
     *
     * DebugTextInterface contains static style information, such as color, outline color and outline thickness.
     * Once you set DebugTextInterface members, they will be active for all the DebugTexts you create afterwards.
     * For example to create a DebugText with a red outline of 1 px
     * \code
     * DebugTextInterface::outline_color = sf::Color::Red;
     * DebugTextInterface::outline_thickness = 1;
     * auto* dbg_txt = new DebugText(&var, "label:", {0, 0});
     * \endcode
     *
     * \see DebugText
     */
    class DebugTextInterface : public sf::Text {
    public:
        static int font_size;           ///< set DebugText font size
        static sf::Color color;         ///< set DebugText color
        static sf::Color outline_color; ///< set DebugText outline color
        static float outline_thickness; ///< set DebugText outline thickness

        /**
         * \brief Updates DebugText values
         */
        virtual void update() = 0;
    };

    /**
     * \brief DebugText evaluates a variable or a method and display the value on the AppWindow
     *
     * It lets you see methods or variables values changing in real time.
     *
     * \tparam T Type of the value to display on the AppWindow
     * \tparam ObjT Object type if creating a DebugText from method address, void otherwise
     */
    template<typename T, typename  ObjT>
    class DebugText : public DebugTextInterface {
    public:
        /**
         * \brief Create a DebugText from variable address
         *
         * \param var_address Address of the variable
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         */
        DebugText(T* var_address, const std::string& label, const sf::Vector2f& position);

        /**
         * \brief Create a DebugText from variable address
         *
         * \param var_address Address of the variable (const)
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         */
        DebugText(const T* var_address, const std::string& label, const sf::Vector2f& position);

        /**
         * \brief Create a DebugText from a lambda function
         *
         * \param fn Lambda function to be evaluated
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         */
        DebugText(std::function<T()> fn, const std::string& label, const sf::Vector2f& position);

        /**
         * \brief Create a DebugText from object and method address
         *
         * \param object_address Address of the object that will evaluate the method
         * \param method_address Address of the method to evaluate
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         */
        DebugText(
            ObjT* object_address,
            std::function<T(ObjT &)> method_address,
            const std::string& label,
            const sf::Vector2f& position
        );

        /**
         * \brief Updates DebugText value
         */
        void update() override;

    private:
        std::string m_label;
        T* m_variable_address = nullptr;
        std::function<T()> m_lambda = nullptr;
        ObjT* m_object_address = nullptr;
        std::function<T(ObjT &)> m_method_address = nullptr;

        DebugText(std::string  label, const sf::Vector2f& position);
    };

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(std::string label, const sf::Vector2f& position) :
    m_label(std::move(label)) {
        setFont(Arial::getFont());
        setCharacterSize(DebugTextInterface::font_size);
        setFillColor(DebugTextInterface::color);
        setOutlineColor(DebugTextInterface::outline_color);
        setOutlineThickness(DebugTextInterface::outline_thickness);
        setPosition(position);
    }

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(T* var_address, const std::string& label, const sf::Vector2f& position) :
    DebugText(label, position) {
        m_variable_address = var_address;
    }

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(const T* var_address, const std::string& label, const sf::Vector2f& position) :
    DebugText(label, position) {
        m_variable_address = (T*) var_address;
    }

    template <typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(std::function<T()> fn, const std::string& label, const sf::Vector2f& position) :
            DebugText(label, position) {
        m_lambda = fn;
    }

    template<typename T, typename ObjT>
    DebugText<T, ObjT>::DebugText(
            ObjT* object_address,
            std::function<T(ObjT &)> method_address,
            const std::string& label,
            const sf::Vector2f& position
    ) : DebugText(label, position) {
        m_method_address = method_address;
        m_object_address = object_address;
    }

    template<typename T, typename ObjT>
    void DebugText<T, ObjT>::update() {
        std::ostringstream stream;
        stream << m_label << " ";
        if (m_variable_address != nullptr)
            stream << *m_variable_address;
        else if (m_lambda != nullptr)
            stream << m_lambda();
        else
            stream << (m_method_address)(*m_object_address);
        setString(stream.str());
    }

}
