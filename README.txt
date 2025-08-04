
# 🔫 Bullet Echo – Tactical Vision-Based Shooter (C++)


## 🧠 General Overview

**Bullet Echo** is a tactical top-down shooter developed in **C++**, featuring a unique **cone-based vision system**, stealth mechanics, and smart AI-driven enemies. The player navigates a dark arena, with limited visibility powered by advanced dynamic lighting. Your mission: **survive, collect power-ups, and eliminate all threats using smart strategy and sharp shooting**.

The game includes:
- Smart enemy behavior using **state machines** and **pathfinding**
- Advanced **light & shadow system** using **Candle + Box2D**
- A fully modular engine using **OOP principles** and **design patterns**
- Multiple screens (menu, game, help, victory, defeat) using a **stacked screen manager**
- Weapons, upgrades, visual feedback, and strategic depth

---

## 🗂️ Key Files and Components

> The project consists of over 70+ modular C++ header files, including:

- `AStarPathfinder.h` – Implements A* pathfinding for enemy navigation
- `Bullet.h`, `Weapon.h`, `Sniper.h`, `Shotgun.h` – Weapon & bullet logic
- `Player.h`, `Enemy.h`, `Character.h` – Core game characters
- `State.h`, `AttackingState.h`, `WalkingState.h` – AI state machine
- `VisionLight.h`, `WeaponLight.h` – Cone-based lighting logic
- `Factory.h`, `Gift.h`, `Spy.h` – Gift system with special mechanics
- `Controller.h`, `Screen.h`, `PauseScreen.h`, `HomeScreen.h` – Scene management
- `TextureManager.h`, `SoundManager.h` – Resource singletons
- `SmartWeaponCommand.h`, `PushScreenCommand.h` – Command pattern actions

---

## 🧱 Data Structures & Patterns

- `std::vector` – Stores bullets, enemies, and dynamic objects
- `std::unordered_map` – Efficient key-based access to textures, sounds, and states
- `std::set` – Maintains unique list of owned weapons
- `std::stack` – Manages screen navigation (LIFO)
- `std::shared_ptr` / `std::weak_ptr` – Smart memory management for all objects

**Programming Concepts Used:**
- Object-Oriented Programming (OOP)
- Factory, State, Strategy, Singleton Patterns
- Clean modular design with reusability in mind

---

## 🔍 Core Mechanics & Logic

### 🎯 Cone Vision
Dynamic vision cone based on direction, raycasted from the player/enemy, blocked by walls. Drives:
- Visibility
- Auto-shooting
- AI detection

### 🔫 Auto Shooting
Player/enemies fire **automatically** if an enemy enters the visible cone and line of sight is clear.

### 🧠 Smart Enemies
Each enemy has AI states: patrol, chase, shoot. Behavior is triggered by visibility and distance. Uses A* for chasing.

### 🎁 Gift System
Collectible power-ups with real-time effects:
- Shield, Speed, Ammo, and a special **Spy gift**
- Spy temporarily converts an enemy to ally

### 💡 Lighting System
Cone lights use Candle & SFML. Efficient raycasting prevents light from penetrating walls. Lights update only when needed.

### 🧱 Wall Interactions
Bullets and lights are blocked by walls. All characters respect collision boundaries via **Box2D**.

---

## 🤝 Object Interaction Map

| Object | Interaction |
|--------|-------------|
| Player | Moves, auto-shoots, collects gifts, takes damage |
| Enemy | AI-driven, reacts to player, chases, shoots |
| Spy | Ally unit created from enemy; supports auto-fire |
| Bullet | Damages target on hit; disappears on collision |
| Gift | Triggered on collection; one-time use |
| Light | Determines visibility, vision cone direction |
| Wall | Blocks movement, bullets, and light rays |

---

## 🐞 Known Bugs

> No known bugs were encountered during testing. The game ran stably across all tested scenarios.

---

## 🧩 Technical Highlights

- 🔧 Built entirely in **C++** using **SFML**, **Box2D**, and **Candle**
- 🎮 Fully **data-driven** via JSON map files (created in Tiled)
- 🧠 Smart AI & reactive enemies
- ⚔️ Four unique weapons with stats: Handgun, Shotgun, Rifle, Sniper
- 🛠️ One-time-loaded textures & sounds using **singleton resource managers**
- 📊 Built for performance, clarity, and expandability

---

## 🌍 Future Improvements (Optional)

- Multiplayer support
- Scoreboards and XP system
- Visual health bars on enemies
- Map editor

---

## 🏁 Summary

**Bullet Echo** demonstrates a strong grasp of:
- Advanced **C++ design**
- **OOP** and modern **software architecture**
- Real-time graphics, physics, and gameplay mechanics

> A complete, professional-grade game project built to impress and scale.

