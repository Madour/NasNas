/**
* Created by Modar Nasser on 01/05/2020.
**/


#pragma once

#include <functional>
#include <sstream>
#include <string>

#include <SFML/Graphics/Text.hpp>

#include <NasNas/core/data/Arial.hpp>

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
     */
    template<typename T>
    class DebugText : public DebugTextInterface {
    public:
        /*
         * \brief Create a DebugText with only a label, and no value
         */
        DebugText(std::string  label, const sf::Vector2f& position);

        /**
         * \brief Create a DebugText from variable address
         *
         * \param var_address Address of the variable
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         */
        DebugText(const std::string& label, T* var_address, const sf::Vector2f& position);

        /**
         * \brief Create a DebugText from a lambda function
         *
         * \param fn Lambda function to be evaluated
         * \param label Label of the DebugText
         * \param position Position of the DebugText on the AppWindow
         */
        DebugText(const std::string& label, std::function<T()> fn, const sf::Vector2f& position);

        /**
         * \brief Updates DebugText value
         */
        void update() override;

    private:
        std::string m_label;
        T* m_variable_address = nullptr;
        std::function<T()> m_lambda = nullptr;
    };

    template <typename T>
    DebugText<T>::DebugText(std::string label, const sf::Vector2f& position) :
    m_label(std::move(label)) {
        setFont(Arial::getFont());
        setCharacterSize(DebugTextInterface::font_size);
        setFillColor(DebugTextInterface::color);
        setOutlineColor(DebugTextInterface::outline_color);
        setOutlineThickness(DebugTextInterface::outline_thickness);
        setPosition(position);
    }

    template <typename T>
    DebugText<T>::DebugText(const std::string& label, T* var_address, const sf::Vector2f& position) :
    DebugText(label, position) {
        m_variable_address = var_address;
    }

    template <typename T>
    DebugText<T>::DebugText(const std::string& label, std::function<T()> fn, const sf::Vector2f& position) :
    DebugText(label, position) {
        m_lambda = fn;
    }

    template<typename T>
    void DebugText<T>::update() {
        std::ostringstream stream;
        stream << m_label << " ";
        if (m_variable_address != nullptr)
            stream << *m_variable_address;
        else if (m_lambda != nullptr)
            stream << m_lambda();
        setString(stream.str());
    }

}
