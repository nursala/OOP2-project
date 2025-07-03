#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <memory>

#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "GameObject/Bullet.h"
#include "LoadMap.h"
#include "DebugDraw.h"
#include "Statusbar.h"
#include "RenderLayers.h"

//======================================================
// World class manages the Box2D world, game entities,
// rendering, and interactions within the current level.
//======================================================
class World {
public:
    // Constructor
    World();

    // Update the entire game world per frame
    void update(sf::RenderWindow& window, float deltaTime);

    // Render everything to the window
    void render(sf::RenderWindow& window);

    // Return the size of the map texture
    const sf::Vector2f getMapTextureSize() const;

    // Access to player
    const Player& getPlayer() const;

    // Access to the Box2D world
    b2World& getWorld();

    // Add bullets created externally (e.g. by weapons)
    void addBullets(std::vector<std::unique_ptr<Bullet>> bullets);

    // Get all enemies as raw pointers
    std::vector<Enemy*> getEnemies() const;

    // Get the list of edges near the light source/view
    std::vector<candle::Edge>& getCloseEdges() { return m_closeEdges; }

private:
    // Initialize world objects and layout
    void initWorld();

    // Setup map texture and walls
    void setMapTexture();
    void setupMap();

    // Create entities
    void createPlayer();
    void createEnemy();
    void createGifts();

    // Modular update functions
    void updateBullets(float deltaTime);
    void updateEnemies(float deltaTime);
    void updateGifts(float deltaTime);

    // Extract and build all map edges
    void buildAllEdges();

    // Calculate which edges are near the current view center
    void calcNearlyEdge(sf::RenderWindow& window);

    // Draw debug edge lines (optional)
    void DebugEdge(sf::RenderWindow& window);

private:
    b2World m_world;                                      // Box2D physics world
    Statusbar m_statusbar;                                // Game status bar
    std::unique_ptr<RenderLayers> m_renderLayers;         // Off-screen render layers
    std::shared_ptr<Player> m_player;                     // Main player entity
    std::vector<std::shared_ptr<Enemy>> m_enemies;        // Enemy entities
    std::vector<std::unique_ptr<Bullet>> m_bullets;       // Active bullets
    std::vector<std::unique_ptr<Gift>> m_gifts;           // Active gifts

    sf::Sprite m_mapSprite;                               // Background map sprite
    LoadMap m_tileMap;                                    // Tile/map loader
    candle::EdgeVector m_allEdges;                        // All map edges
    std::vector<candle::Edge> m_closeEdges;               // Edges near the light source/view

    static constexpr float SCALE = 30.f;                  // Scale between pixels and Box2D units
    bool m_gameOver = false;                              // Game over flag
};
