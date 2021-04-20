<h1 align=center>NasNas</h1>
<h3 align=center> An intuitive and user friendly 2D game framework for C++. </h3>
<p align=center>
 <a href=https://travis-ci.com/Madour/NasNas><img src=https://travis-ci.com/Madour/NasNas.svg?branch=master></a>
 <a href=https://www.codacy.com/manual/Madour/NasNas><img src=https://app.codacy.com/project/badge/Grade/23bdd1079c3f4274a712f42851a276d8></a>
 <a href="https://lgtm.com/projects/g/Madour/NasNas/context:cpp"><img alt="Language grade: C/C++" src="https://img.shields.io/lgtm/grade/cpp/g/Madour/NasNas.svg?logo=lgtm&logoWidth=18"/></a>
 <a href="https://lgtm.com/projects/g/Madour/NasNas/alerts/"><img alt="Total alerts" src="https://img.shields.io/lgtm/alerts/g/Madour/NasNas.svg?logo=lgtm&logoWidth=18"/></a>
</p>
<p align=center>
 <a href=#features>Features</a> •
 <a href=#build>How to build</a> •
 <a href=#get-started>Get Started</a> •
 <a href=#showcase>Showcase</a> •
 <a href=#support>Support</a>
</p>

# 

**NasNas** is a lightweight **cross platform** modular **2D game framework**.

It is entirely written in **modern C++17**, and doesn't have any dependency other than SFML2.

It provides a **clean** and **easy to use** API.

The framework is separated in multiple independent modules :
- ***Core*** is the only non optional modules. They are needed to create a NasNas application. 
They contain core classes and data needed by the framework.
- ***Reslib*** contains the resource manager and resource loader. It handles resource loading and accessing in
a very elegant way.
- ***ECS*** contains the BaseEntity and Components classes. Add Components to BaseEntity derived classes to add more
  functionalities to them, like graphics, physics, collider, inputs... Or create and add your own customized components.
- ***Tilemapping*** is a Tiled Map loader (.tmx). It seamlessly integrates with NasNas and speeds up development
for tile based games.
- ***UI*** contains the User Interface utilities. (WIP)
- More modules will be developed in the future !

# 

### Features

##### Implemented :
 - [x] **Scene** and Layers system
 - [x] **Cameras** and Shaders
 - [x] Automatic **resource loader and  manager** system
 - [x] **Entities** and **components** (animated sprites, shapes, physics, inputs, collider, customized components ...) 
 - [x] **Tiled map loader** (.tmx)
 - [x] Text and **bitmap fonts**
 - [x] **Transitions**
 - [x] Multi texture **SpriteBatching**
 - [x] Global app configuration settings
 - [x] Debug text display in-game
 - [x] Convenient console **Logger**

##### In Progress:
 - [ ] Particles system

##### To do :
 - [ ] Menus and UI

 
##### Future :
 - [ ] Splash screens
 - [ ] Levels and game events management
 - [ ] In-game command line for debugging


### Build

Clone the repository (with `--recurse` if you don't have SFML already installed on your computer). Then, you can build :
```bash
mkdir build && cd build
cmake ..
cmake --build . -j4
```
This will build the static library libNasNas.a (NasNas.lib on windows).

Additional CMake options you can pass : 

- `-DNASNAS_FIND_SFML=OFF` to build SFML as a submodule inside the project (this will be OFF automatically if SFML is not found)
- `-DNASNAS_EXAMPLES=ON` to create the example applications targets
- `-DNASNAS_BUILD_RESLIB=OFF` to disable the *Reslib* module
- `-DNASNAS_BUILD_ECS=OFF` to disable the *ECS* module
- `-DNASNAS_BUILD_TILEMAPPING=OFF` to disable the *Tilemapping* module
- `-DNASNAS_BUILD_UI=OFF` to disable the *UI* module



### Get Started

Here is a sample code using NasNas framework, this will create a 720x480 window and log a string to the console : 

```c++
#include <NasNas.h>

class Game : public ns::App {
public:
    Game() : ns::App("My game", 720, 480) {
        ns_LOG("Created a NasNas app !");
    }
    void onEvent(const sf::Event& event) override {
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

A complete **tutorial** to learn how to use the framework can be found on the **[wiki](https://github.com/Madour/NasNas/wiki)**. 

**Documentation** can be found **[here](https://madour.github.io/NasNas/doc)**.

You can also check **[examples](https://github.com/Madour/NasNas/tree/master/examples)** source code
for an overview of what you can do with the framework.

### Showcase

The following games were made with NasNas :

- Warp Runner on [itch](https://madour.itch.io/warp-runner) - source code not available (yet)
- History Leaks on [itch](https://madour.itch.io/history-leaks) and [github](https://github.com/Madour/GB_OLC_Jam2020)
- Cyber Slayer on [github](https://github.com/Madour/CyberSlayer)


### Support

If you like the project, please consider starring this repository.

### Author

 - Modar Nasser
 