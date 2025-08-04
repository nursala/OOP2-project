<h1 align="center">🔫 Bullet Echo – Tactical Vision-Based Shooter (C++)</h1>

<p align="center">
  A stealth-based top-down shooter built with C++, featuring dynamic cone vision, smart AI enemies, and modular game architecture.<br>
  Powered by <strong>SFML + Box2D + Candle</strong>, built with <strong>OOP</strong> and modern <strong>Design Patterns</strong>.
</p>

<p align="center">
  <img src="https://media.giphy.com/media/l3vR85PnGsBwu1PFK/giphy.gif" width="300" alt="Preview GIF">
</p>

---

## 🧠 General Overview

**Bullet Echo** is a fast-paced tactical shooter where the player navigates a dark map with limited vision. Enemies appear unexpectedly, react to your movement, and engage in strategic combat. The player must **survive, collect gifts, and eliminate enemies** using intelligent movement and auto-shooting.

> The project emphasizes:
> - Dynamic **cone-based lighting** using raycasting
> - Smart **AI behavior** with finite states and pathfinding
> - Modular scene and resource management
> - Clean, scalable architecture with modern C++ standards

---

## 🗂️ Key Components

- 🎯 `AStarPathfinder.h` – A* pathfinding for AI navigation  
- 🔫 `Weapon.h`, `Bullet.h`, `Sniper.h` – Weapons & projectiles  
- 🧠 `State.h`, `AttackingState.h`, `WalkingState.h` – AI states  
- 👁️ `VisionLight.h`, `WeaponLight.h` – Light cone system  
- 🎁 `Gift.h`, `Spy.h` – Unique power-ups like the Spy mode  
- 🧭 `Controller.h`, `Screen.h` – Scene management with stack logic  
- 🎨 `TextureManager.h`, `SoundManager.h` – Singleton resource loaders  
- 💡 Over **70 modular headers** for every game component

---

## 🧱 Data Structures & Patterns

| Feature | Usage |
|--------|-------|
| `std::vector` | Dynamic object lists (enemies, bullets...) |
| `std::unordered_map` | Fast access to textures/sounds/states |
| `std::set` | Unique purchased weapons |
| `std::stack` | Screen navigation (LIFO) |
| `std::shared_ptr` / `std::weak_ptr` | Safe memory management |

🔄 Uses major **Design Patterns**:
- **Factory** for object creation
- **Strategy** for AI movement
- **State** for AI behavior
- **Singleton** for shared resources

---

## 🔍 Core Mechanics

### 🔦 Cone Vision
- Player/enemies have limited visibility using raycast-based cone lighting
- Light blocked by walls
- Drives auto-shooting and AI behavior

### 🎯 Auto Shooting
- Enemies are automatically shot when inside the vision cone and visible
- No need for manual fire

### 🎁 Gift System
- Gifts grant speed, armor, ammo, or even convert an enemy into a **temporary ally** (Spy)

### 🧠 Smart AI
- Patrol → Detect → Chase → Attack logic
- Uses A* for pathfinding around walls

---

## 🤝 Interaction Summary

| Object | Role |
|--------|------|
| **Player** | Moves, collects gifts, shoots automatically |
| **Enemy** | State-based AI, chases and attacks |
| **Spy** | Temporarily joins player team and shoots enemies |
| **Bullet** | Deals damage on contact, removed on collision |
| **Wall** | Blocks movement, bullets, and vision |
| **Gift** | One-time pickup with immediate effect |
| **Light** | Drives vision and auto-shoot system |

---

## 🐞 Stability

✅ Game was tested thoroughly — no known bugs or crashes.  
🧪 Physics and light interactions verified across edge cases.

---

## 🧩 Technical Highlights

- 💻 Written entirely in **C++**
- 🧱 Uses **SFML** for rendering and **Box2D** for physics
- 💡 **Candle** for dynamic light rays and cone vision
- 🧠 Modular enemy AI with strategy & state transitions
- 📦 JSON level loading via **Tiled Map Editor**
- 🛠️ Asset managers for textures & sounds (singleton pattern)

---

## 🚀 Future Enhancements

- Online multiplayer
- Scoreboard and progression
- Enemy health bars
- Map editor integration

---

## 🏁 Summary

> Bullet Echo is more than a game – it's a **portfolio project** demonstrating mastery in:
> - Modern **C++ architecture**
> - Real-time rendering & physics
> - AI and lighting systems
> - Scalable, clean, and testable design

---

### 👥 Developers

- 🎮 עאמר אבו סיר – 325535193  
- 🎮 נור צלאח – 212427603  
- 🎮 שאדי יונס – 325129385

---

## 📸 Screenshots / Demo

> _(Add real gameplay screenshots or a video demo here to boost interest!)_

---

🧠 **Want to know more?**  
Check the source code, open an issue, or contact us on LinkedIn!

