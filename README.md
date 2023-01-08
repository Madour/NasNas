<p align=center><img width=500px align=center src="https://i.ibb.co/r3RdmN8/Nas-Nas-title.png" alt="NasNas-logo"></p>
<h3 align=center> An intuitive and beginner friendly 2D game framework for C++. </h3>
<p align=center>
 <a href=https://github.com/Madour/NasNas/actions/workflows/cmake.yml><img src=https://github.com/Madour/NasNas/actions/workflows/cmake.yml/badge.svg></a>
 <a href=https://github.com/Madour/NasNas/actions/workflows/codeql.yml><img src=https://github.com/Madour/NasNas/actions/workflows/codeql.yml/badge.svg></a>
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

The framework is separated in multiple modules :
- ***Core*** is the only non-optional module. It is needed to create a NasNas application. 
  It contains core classes and data needed by the framework.
- ***ECS*** is an efficient data driven Entity Component System.
  It allows you to attach components to entities and run systems on specific sets of components.
- ***Reslib*** contains the resource manager and resource loader. It handles resource loading and accessing in
  an elegant way.
- ***Tilemapping*** is a Tiled Map loader (.tmx). It seamlessly integrates with NasNas and speeds up development
  for tile based games.
- ***Tween*** allows you to animate any object using the provided or custom easing functions.
- ***UI*** contains the User Interface utilities. (WIP)
- More modules will be developed in the future !

<details>
  <summary>Click to see platforms support</summary>

|         | Core               | Ecs                | Reslib             | Tilemapping        | Tween              | Ui                 |
|---------|--------------------|--------------------|--------------------|--------------------|--------------------|--------------------|
| Windows | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| Linux   | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| MacOS   | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| Android | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: | :heavy_check_mark: |
| iOS     | :question:         | :question:         | :question:         | :question:         | :question:         | :question:         |

</details>

# 

### Features

##### Implemented :
- [x] **Scene** and Layers system
- [x] **Cameras** and Shaders
- [x] Application **states** (using StateStackApp or StateMachineApp)
- [x] Automatic **resource loader and  manager**
- [x] Data oriented ECS inspired by entt with a bunch of provided components and defaults systems. 
- [x] **Tiled map loader** (.tmx)
- [x] Text and **bitmap fonts**
- [x] Customizable **Transitions**
- [x] Flexible **Tween** and **MultiTween** utilities.
- [x] Extensible **Particles system**
- [x] Multi texture **SpriteBatching**
- [x] App configuration and settings
- [x] Debug text display in-game
- [x] Convenient console **Logger**
- [x] And more !

##### To do :
- [ ] Menus and UI

##### Future :
- [ ] Splash screens
- [ ] Levels and game events management
- [ ] In-game command line for debugging

You can find a global roadmap for the version 1.0 on the [project board](https://github.com/Madour/NasNas/projects/1) 


### Build

#### Desktop

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

#### Android

To build the framework for Android, please refer to the [Android example's readme](https://github.com/Madour/NasNas/tree/master/examples/android)

#### Available CMake options : 

- `-DNASNAS_BUILD_ECS=OFF` to disable the *ECS* module
- `-DNASNAS_BUILD_RESLIB=OFF` to disable the *Reslib* module
- `-DNASNAS_BUILD_TILEMAPPING=OFF` to disable the *Tilemapping* module
- `-DNASNAS_BUILD_TWEEN=OFF` to disable the *Tween* module
- `-DNASNAS_BUILD_UI=OFF` to disable the *UI* module


- `-DNASNAS_EXAMPLES=ON` to create the example applications targets
- `-DNASNAS_BUILD_SFML=ON` to download and build SFML inside the project (enabled automatically if SFML package is not found)
- `-DNASNAS_STATIC_VCRT=ON` to link the Visual C++ runtime statically (/MT) when using the Microsoft Visual C++ compiler

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

All of these programs source code can be found in the `examples` folder.

#### Split View

![2021-09-02_12-15-46](https://user-images.githubusercontent.com/11854124/131828318-8203a8c2-7ad2-4a7b-ab6a-938feb3d4dd2.gif)

#### Line paint

![2021-09-02_12-17-09](https://user-images.githubusercontent.com/11854124/131828374-e9e618ec-1d71-412e-94cc-15de075fac63.gif)

#### Tweening

![2021-09-02_12-17-56](https://user-images.githubusercontent.com/11854124/131828412-122481a1-28ae-4272-8852-0de6f0ba33cf.gif)
 
#### Animated sprites
 
![animated_sprites-d_zZDAUUAIOb](https://user-images.githubusercontent.com/11854124/170838730-1756a3bd-9505-4cbf-9852-9d1e7360ca83.gif)
 
#### Particles System

https://user-images.githubusercontent.com/11854124/131836256-553ec86b-54c2-4145-b2c5-f1229b282d7e.mp4

#### Parallax platformer demo game
 
##### Desktop 
https://user-images.githubusercontent.com/11854124/131836274-4363d86d-cbf3-4358-800c-841b347efd89.mp4

##### Android
https://user-images.githubusercontent.com/11854124/146814302-29f5f9be-3032-448f-987c-3967b5ed9689.mp4
 

### Showcase

#### Games

The following games were created with NasNas :

- Warp Runner on [itch](https://madour.itch.io/warp-runner) (Desktop)
- History Leaks on [itch](https://madour.itch.io/history-leaks) and [github](https://github.com/Madour/GB_OLC_Jam2020) (Desktop)
- Cyber Slayer on [github](https://github.com/Madour/CyberSlayer) (Desktop and Android)

#### Other

<details>
    <summary>A simple physics engine made with NasNas only</summary>

https://user-images.githubusercontent.com/11854124/131828997-5d3b1635-934f-4e89-8250-f9fcba9410ef.mp4
 
</details>

### Support

If you like the project, please consider starring this repository. 

If you would like to discuss anything about the project, feel free to open a new [discussion](https://github.com/Madour/NasNas/discussions).

### Author

- Modar Nasser
 
