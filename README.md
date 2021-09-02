<p align=center><img width=500px align=center src="https://i.ibb.co/r3RdmN8/Nas-Nas-title.png" alt="NasNas-logo"></p>
<h3 align=center> An intuitive and beginner friendly 2D game framework for C++. </h3>
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
 <a href=#screenshots>Screenshots</a> •
 <a href=#showcase>Showcase</a> •
 <a href=#support>Support</a>
</p>

# 

**NasNas** is a lightweight **cross platform** modular **2D game framework**.

It is entirely written in **modern C++17**, and uses SFML2 for rendering.

It provides a **clean** and **easy to use** API.

The framework is separated in multiple independent modules :
- ***Core*** is the only non-optional module. It is needed to create a NasNas application. 
It contains core classes and data needed by the framework.
- ***Reslib*** contains the resource manager and resource loader. It handles resource loading and accessing in
an elegant way.
- ***ECS*** is an efficient data driven Entity Component System.
It allows you to attach components to entities and run systems on specific sets of components.
- ***Tilemapping*** is a Tiled Map loader (.tmx). It seamlessly integrates with NasNas and speeds up development
for tile based games.
- ***Tween*** allows you to animate any object using various easing functions.
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
- [x] Flexible **Tween** and **MultiTween** utilities.
- [x] Multi texture **SpriteBatching**
- [x] App configuration and settings
- [x] Debug text display in-game
- [x] Convenient console **Logger**
- [x] And more !

##### In Progress:
- [ ] Particles system

##### To do :
- [ ] Menus and UI

 
##### Future :
- [ ] Splash screens
- [ ] Levels and game events management
- [ ] In-game command line for debugging

You can find a very global roadmap for the version 1.0 on the [project board](https://github.com/Madour/NasNas/projects/1) 


### Build

Clone the repository. 
```bash
git clone https://github.com/Madour/NasNas
cd NasNas
```

Then, you can build the static libraries with :
```bash
mkdir build && cd build
cmake ..
cmake --build . -j4
```

Finally, you can install those libraries using :

```bash
cmake --install .
```

Additional CMake options you can pass : 

- `-DNASNAS_BUILD_RESLIB=OFF` to disable the *Reslib* module
- `-DNASNAS_BUILD_ECS=OFF` to disable the *ECS* module
- `-DNASNAS_BUILD_TILEMAPPING=OFF` to disable the *Tilemapping* module
- `-DNASNAS_BUILD_UI=OFF` to disable the *UI* module


- `-DNASNAS_EXAMPLES=ON` to create the example applications targets
- `-DNASNAS_BUILD_SFML=ON` to download and build SFML inside the project (enabled automatically if SFML package is not found)


### Get Started

Here is a sample code using NasNas framework, this will create a 720x480 window and log a string to the console : 

```c++
#include <NasNas/Core.hpp>

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

An introduction **tutorial** to learn how to use the framework can be found on the **[wiki](https://github.com/Madour/NasNas/wiki)**. 

**Documentation** can be found **[here](https://madour.github.io/NasNas/doc)**.

You can also check **[examples](https://github.com/Madour/NasNas/tree/master/examples)** source code
for a small overview of what you can do with the framework.

### Screenshots

<details>
  <summary>Click to take a look at the examples provided with NasNas</summary>

All of these programs source code can be found in the `examples` folder.

#### Split View

![2021-09-02_12-15-46](https://user-images.githubusercontent.com/11854124/131828318-8203a8c2-7ad2-4a7b-ab6a-938feb3d4dd2.gif)

#### Line paint

![2021-09-02_12-17-09](https://user-images.githubusercontent.com/11854124/131828374-e9e618ec-1d71-412e-94cc-15de075fac63.gif)

#### Tweening

![2021-09-02_12-17-56](https://user-images.githubusercontent.com/11854124/131828412-122481a1-28ae-4272-8852-0de6f0ba33cf.gif)
 
#### Particles System

https://user-images.githubusercontent.com/11854124/131836256-553ec86b-54c2-4145-b2c5-f1229b282d7e.mp4

#### Parallax platformer demo game

https://user-images.githubusercontent.com/11854124/131836274-4363d86d-cbf3-4358-800c-841b347efd89.mp4

</details>

### Showcase

#### Games

The following games were created with NasNas :

- Warp Runner on [itch](https://madour.itch.io/warp-runner) - source code not available (yet)
- History Leaks on [itch](https://madour.itch.io/history-leaks) and [github](https://github.com/Madour/GB_OLC_Jam2020)
- Cyber Slayer on [github](https://github.com/Madour/CyberSlayer)

#### Other

<details>
    <summary>A simple physics engine made with NasNas only</summary>

https://user-images.githubusercontent.com/11854124/131828997-5d3b1635-934f-4e89-8250-f9fcba9410ef.mp4
 
</details>

### Support

If you like the project, please consider starring this repository.

### Author

- Modar Nasser
 
