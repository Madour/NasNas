/**
* Created by Modar Nasser on 21/04/2020.
**/


#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#ifdef __ANDROID__
#include <android/log.h>
#endif
#include <SFML/Graphics.hpp>
#include "NasNas/core/data/Utils.hpp"

/**
 * \brief Logs a variable number of variable to the console.
 *
 * The logged string will contain location information : line number and file name
 * from where the macro was called
 */
#define ns_LOG(...) ns::Logger::log(__FILE__, __LINE__, __VA_ARGS__)

namespace sf {
    auto operator<<(std::ostream& os, const sf::Vector2f& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector2i& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector2u& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector3f& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Vector3i& vect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::FloatRect& rect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::IntRect& rect) -> std::ostream&;
    auto operator<<(std::ostream& os, const sf::Color& color) -> std::ostream&;
}

namespace ns {
#ifdef __ANDROID__
    namespace detail {
        class AndroidStreamBuffer : public std::streambuf {
        public:
            AndroidStreamBuffer();
            auto overflow (std::streambuf::int_type c) -> std::streambuf::int_type override;
        private:
            std::string m_buffer;
        };

        static AndroidStreamBuffer logger_buffer;
    }
    static std::ostream LoggerStream(&detail::logger_buffer);
#else
    static auto& LoggerStream = std::cout;
#endif

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
        Logger() = default;

        template <typename T, typename... Types>
        static void logr(T arg, Types... args);
    };

    template<typename... Types>
    void Logger::log(const std::string& file, int line_nb, Types... args) {
        LoggerStream << std::boolalpha << "["<<line_nb<<"|"<<ns::utils::path::getFilename(file)<<"] ";
        logr(args...);
    }

    template <typename T, typename... Types>
    void Logger::logr(T arg, Types... args) {
        LoggerStream << arg << " ";
        if constexpr(sizeof...(args) == 0) {
            LoggerStream << std::endl;
        } else {
            logr(args...);
        }
    }

}
