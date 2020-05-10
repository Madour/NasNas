/**
* Created by Modar Nasser on 21/04/2020.
**/

#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#define ns_LOG(...) ns::Logger::log(__FILE__, __LINE__, __VA_ARGS__)

namespace ns {

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
        std::cout << arg << " ";
        Logger::logr(args...);
    }
}

