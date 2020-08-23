/**
* Created by Modar Nasser on 21/04/2020.
**/


#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include "SFML/Graphics.hpp"

/**
 * \brief Logs a variable number of variable to the console.
 *
 * The logged string will contain location information : line number and file name
 * from where the macro was called
 */
#define ns_LOG(...) ns::Logger::log(__FILE__, __LINE__, __VA_ARGS__)

namespace ns {

    auto operator<<(std::ostream& os, const sf::Vector2f& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector2i& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector2u& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector3f& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector3i& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::FloatRect& rect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::IntRect& rect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Color& color) -> std::ostream&;

    /**
     * \brief Console Logger can log a variable number of variables to the console.
     *
     * Variables must have operator<< function overload.
     * Logger class is not intended to be used directly. Instead you should use ns_LOG macro.
     * \see ns_LOG
     */
    class Logger {
    public:
        template <typename... Types>
        static void log(const std::string& file, int line_nb, Types... args);

    private:
        template <typename T, typename... Types>
        static void logr(T arg, Types... args);

        static void logr();
        Logger() = default;
    };

    template<typename... Types>
    void Logger::log(const std::string& file, int line_nb, Types... args) {
        std::cout << "["<<line_nb<<"|"<<std::filesystem::path(file).filename().string()<<"] ";
        Logger::logr(args...);
    }

    template <typename T, typename... Types>
    void Logger::logr(T arg, Types... args) {
        std::cout << std::boolalpha << arg << " ";
        Logger::logr(args...);
    }

}
