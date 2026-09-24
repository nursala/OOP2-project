
<h1 align="center">🔫 Bullet Echo – Tactical Vision-Based Shooter (C++)</h1>

<p align="center">
  A stealth-based top-down shooter built with C++, featuring dynamic cone vision, smart AI enemies, and modular game architecture.<br>
  Powered by <strong>SFML + Box2D + Candle</strong>, crafted with <strong>Clean Code</strong>, <strong>OOP</strong>, and modern <strong>Design Patterns</strong>.
</p>

<p align="center">
  <a href="https://www.youtube.com/watch?v=JL1c-vySePA"><img src="https://img.youtube.com/vi/JL1c-vySePA/hqdefault.jpg" width="480" alt="Watch the project gameplay video"></a>
</p>

---

## 🎮 About the Game

**Bullet Echo** is a high-stakes, real-time tactical shooter where visibility is everything.  
You control a lone fighter navigating a dark arena, relying on a **cone-shaped vision** system to spot enemies and survive.

🧠 **Enemies are smart**, they react to your movement, chase you, and fire back — unless you outsmart them first.  
Your goal: **Collect power-ups, eliminate threats, and adapt to survive**.

---

## ✨ Key Features

- 🔦 **Cone Vision System** – Realistic dynamic light cone based on raycasting and direction
- 🤖 **Advanced Enemy AI** – State machine logic with detection, chasing, attacking, and A* pathfinding
- 🎯 **Auto Shooting** – Enemies and the player shoot automatically when visibility is clear
- 🧠 **Spy Gift System** – Temporarily convert enemies into allies with autonomous behavior
- 💡 **Light Interactions** – Walls block light rays and bullets; dynamic updates for performance
- 🔫 **Weapon Variety** – Includes Handgun, Rifle, Shotgun, and Sniper with different mechanics
- 🎁 **Power-Ups** – Speed boost, shield, ammo refill, or recruit a temporary ally
- 🧱 **JSON-Based Map Loading** – Build levels visually with Tiled and load them via JSON
- 🎨 **Stacked Screen Navigation** – Smooth scene transitions using a custom screen manager
- 🎵 **Sound & Resource Management** – Singleton pattern ensures optimal loading and reuse

---

## 🗂️ Major Components

- `AStarPathfinder.h` – A* algorithm for smart AI navigation  
- `VisionLight.h`, `WeaponLight.h` – Cone vision with Candle  
- `Player.h`, `Enemy.h`, `Spy.h` – Character logic and behavior  
- `State.h`, `AttackingState.h`, `WalkingState.h` – State machine for AI  
- `Bullet.h`, `Weapon.h`, `Sniper.h`, `Rifle.h` – Shooting system  
- `Gift.h` – Power-up effects (including spy transformation)  
- `Controller.h`, `Screen.h`, `Market.h`, `PauseScreen.h` – Full game scene system  
- `SoundManager.h`, `TextureManager.h` – Efficient resource managers  
- `Command.h` – Executes actions like StartGame, Exit, BuyWeapon using the Command Pattern

---

## 🧱 Architecture & Design

| Tool | Purpose |
|------|---------|
| `std::vector` | Stores bullets, enemies, etc. |
| `std::unordered_map` | Fast access to textures, sounds |
| `std::stack` | Manages screens (Home, Game, Help...) |
| `std::set` | Tracks unique owned weapons |
| `std::shared_ptr`, `std::weak_ptr` | Memory-safe entity management |

### ✅ Patterns Implemented

- 🔨 **Factory** – Dynamic object creation (Gifts, Bullets, Enemies...)
- 🧠 **State Pattern** – Enemy behavior transitions (patrol → chase → attack)
- 🧭 **Strategy Pattern** – Different AI and movement styles
- 📦 **Singleton** – Shared resource managers (textures, audio)
- 🧱 **Modular OOP Structure** – Easy to scale and maintain

---

## 🎯 Core Mechanics

### 🔦 Cone Vision
- Limited vision via raycasting from player/enemy direction
- Blocked by walls and obstacles
- Determines shooting, detection, and visibility

### 🎯 Auto Shooting
- No manual firing needed
- AI or player fires when enemy is visible in light cone

### 🎁 Gift System
- Power-ups include:
  - 🛡️ Shield (absorbs damage)
  - ⚡ Speed boost
  - 🔫 Ammo refill
  - 🕵️ Spy (temporary ally from enemy)

### 🤖 Enemy AI
- State-based: patrol, chase, shoot
- Switches intelligently based on visibility and proximity
- Pathfinding with A*

---

## 🤝 Object Interaction Map

| Object | Behavior |
|--------|----------|
| **Player** | Moves, auto-shoots, collects gifts |
| **Enemy** | State-driven AI: attacks player, patrols |
| **Spy** | AI ally that follows player and auto-shoots enemies |
| **Bullet** | Damages target, disappears on impact |
| **Gift** | Grants immediate effect, one-time use |
| **Wall** | Blocks light, bullets, movement |
| **Light** | Raycasted, defines visibility cone and engagement |

---

## 🐞 Stability & Performance

✅ Game tested in various edge cases.  
🧪 Stable physics, collision, and lighting behavior.  
♻️ Efficient rendering and updates thanks to modular structure and smart resource reuse.

---

## Preview

🎥 **Video Preview:**  
https://www.youtube.com/watch?v=JL1c-vySePA  
Click the video thumbnail above to see the gameplay.

---

## 🛠️ Technologies Used

- 💻 **C++**
- 🖼️ **SFML** – Graphics and windowing
- 🧱 **Box2D** – Physics and collision
- 🔦 **Candle** – Dynamic cone lighting
- 🗺️ **Tiled Editor** – JSON map creation

---

## 🚀 Possible Future Features

- Multiplayer Mode  
- Player Progression / XP  
- Map Editor  
- Health bars above enemies  
- Weapon attachments or upgrades

---

## 🏁 Conclusion

**Bullet Echo** is a fully playable game built with production-level techniques and clean code practices.  
It's a **portfolio-grade project** that showcases deep understanding of:

- 🔹 Game design
- 🔹 Modern C++ architecture
- 🔹 Real-time AI and lighting systems
- 🔹 Data-driven development

> 🎯 A complete tactical experience — designed, built, and optimized from the ground up.
