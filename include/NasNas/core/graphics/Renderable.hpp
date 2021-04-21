// Created by Modar Nasser on 21/04/2021.

#pragma once

#include <vector>

namespace ns {
    class App;

    class Renderable {
        friend App;
    protected:
        Renderable();
        virtual ~Renderable();
        virtual void render() = 0;
    private:
        static std::vector<Renderable*> list;
    };
}

