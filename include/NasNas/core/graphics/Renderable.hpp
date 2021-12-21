// Created by Modar Nasser on 21/04/2021.

#pragma once

#include <vector>

namespace ns {
    class Renderable {
        friend class App;
    public:
        Renderable();
        virtual ~Renderable();
    private:
        static std::vector<Renderable*> list;
        virtual void render() = 0;
    };
}

