# Bullet Echo
**C++ · SFML · Box2D · Candle · CMake**

A tactical top-down shooter built as a team OOP course project. Limited cone vision determines what characters can see and when they can fire, while enemies navigate the arena and respond to the player.

[![Watch Bullet Echo gameplay](https://img.youtube.com/vi/JL1c-vySePA/hqdefault.jpg)](https://www.youtube.com/watch?v=JL1c-vySePA)

**[Watch the gameplay demo](https://www.youtube.com/watch?v=JL1c-vySePA)**

## Features
- Cone lighting and line-of-sight interactions with walls.
- Enemy states, movement strategies, and A* pathfinding.
- Automatic shooting, multiple weapon types, and collectible power-ups.
- A temporary ally mechanic through the Spy gift.
- JSON maps created with Tiled.
- Screen navigation, level selection, a weapon market, audio, and shared resources.

## Engineering highlights
| Concept | Implementation |
| --- | --- |
| Pathfinding | [AStarPathfinder](include/AStarPathfinder.h) |
| Enemy behavior | [State classes](include/StatesInc/) and [movement strategies](include/MoveStrategyAndInfoInc/) |
| Visibility | [VisionLight](include/VisionLight.h) |
| UI actions | [Command classes](include/CommandInc/) |
| Shared assets | [Resource managers](include/ResourseInc/) |
| Physics and lighting dependencies | [Box2D](external/box2d/) and [Candle](external/candle/) |

## Build and run
The repository includes Box2D and Candle sources. Its current CMake configuration targets **Windows**, with SFML **2.6.1** at `C:/SFML/SFML-2.6.1`.

1. Install CMake **3.26+**, a compatible C++ compiler, and matching SFML binaries.
2. Update `SFML_LOCATION` in `CMakeLists.txt` if your installation uses another path.
3. Configure and build from a developer terminal:

```powershell
git clone https://github.com/nursala/OOP2-project.git
cd OOP2-project
cmake -S . -B build
cmake --build build --config Release
```

Run the generated `oop2_project` executable with `build` as its working directory so it can find the copied maps, textures, fonts, and sounds. Multi-configuration generators may place the executable under `build/Release`.

## Scope
The linked video shows the original project demonstration. Cross-platform packaging, automated gameplay coverage, and performance benchmarks are not documented.

## Team
Amer Abu Sair · Nour Salah · Shadi Younis

Third-party dependencies retain their own licenses and attribution.
