# NasNas 
[![Build Status](https://travis-ci.com/Madour/NasNas.svg?branch=master)](https://travis-ci.com/Madour/NasNas)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/23bdd1079c3f4274a712f42851a276d8)](https://www.codacy.com/manual/Madour/NasNas?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Madour/NasNas&amp;utm_campaign=Badge_Grade) 
### A simple game framework to get started quickly with C++ SFML game development.

#### Features :
 - [x] Automatic resource loader and  manager system
 - [x] Scene and Layers system
 - [x] Cameras
 - [x] Entities and components (animated sprites, shapes, physics, inputs) 
 - [x] Debug text display in-game
 - [x] Convenient console Logger
 - [x] Global app configuration settings
 - [x] Text and bitmap fonts
 
#### In progress :
 - [x] Tiled map loader (.tmx)

#### To do :
 - [ ] Transitions
 - [ ] Menus and UI
 
#### Future
 - [ ] Particles system
 - [ ] Splash screens
 - [ ] Levels and game events management
 - [ ] In-game command line for debugging


#### Build

This project uses Cmake. To build (Linux and Windows, not tested on macOS):
```bash
mkdir build
cd build
cmake ..
cmake --build . -j4
```
This will generate a shared library, a static library and the demo application.

If Cmake is unable to find your SFML install location, configure CMakeLists.txt by
setting SFML_ROOT variable. 

#### Get Started

Here is a sample code using NasNas framework, this will create a 720x480 window and log a string to the console : 

```c++
#include "NasNas.h"

class Game : public ns::App {
public:
    Game() : ns::App("My game", 720, 480) {
        ns_LOG("Created a NasNas app !");
    }
    void onEvent(sf::Event event) override {
        if (event.type == sf::Event::Closed)
            getWindow().close();
    }
    void update() override {}
};

int main() {
    Game g;
    g.run();
    return 0;
}
```

Please check the [example game](https://github.com/Madour/NasNas/tree/master/example) source code
for a more complete overview of what you can do with the framework.

Documentation (work in progress) can be found [here](https://madour.github.io/NasNas/doc).

A step by step tutorial to learn how to use the features will be written soon™ . 

#### Support

If you like the project, please consider starring this repository.

#### Other

NasNas also exists for python, check it out [here](https://github.com/Madour/pyNasNas).

#### Author

 - Modar Nasser
 