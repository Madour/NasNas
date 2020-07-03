# NasNas
### A simple game framework to get started quickly with C++ SFML game development.

### Features :
 - [x] Automatic resource loader and  manager system
 - [x] Scene and Layers system
 - [x] Cameras
 - [x] Entities anc components (animated sprites, shapes, physics, inputs) 
 - [x] Debug text display in-game
 - [x] Convenient console Logger
 - [x] Global app configuration settings
 - [x] Text and bitmap fonts
 
### To do :
 - [ ] Tiled map loader (.tmx)
 - [ ] Transitions
 - [ ] Menus and UI
 
### Future
 - [ ] Splash screens
 - [ ] Levels and game events management
 - [ ] In-game command line for debugging
 - [ ] Particles system


### Build

This project uses Cmake. To build :
```bash
mkdir build
cd build
cmake ..
make
```
Feel free to configure CmakeLists.txt file if Cmake is unable to find your SFML install location. 

### Demo code

Please check the [example game](https://github.com/Madour/NasNas/tree/master/example) source code
to get an idea of how the framework is used. A proper wiki and documentation will be written in the future.

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

### Other

NasNas also exists for python, check it out [here](https://github.com/Madour/pyNasNas).

### Author

 - Modar Nasser
 