#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
struct Layer {
    std::string name;
    std::vector<int> tiles;
};

class LoadMap {
public:
    LoadMap(const std::string& jsonPath);

    void createCollisionObjects(b2World& world, const std::string& layerName);

    void parseSpawnLayer(const std::string& layerName, const int playerId, const int enemyId, const int giftId);

    const sf::Vector2f getPlayerSpawns() const;
    const std::vector<sf::Vector2f>& getEnemySpawns() const;
    const std::vector<sf::Vector2f>& getGiftSpawns() const;


    bool isWalkable(const int x, const int y) const;

    // Getters for map properties
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getTileWidth() const { return m_tileWidth; }
    int getTileHeight() const { return m_tileHeight; }

private:
  

    int m_width;
    int m_height;
    int m_tileWidth;
    int m_tileHeight;

    std::vector<Layer> m_layers;

    sf::Vector2f m_playerSpawn;
    std::vector<sf::Vector2f> m_enemySpawns;
    std::vector<sf::Vector2f> m_giftSpawns;

    void addLayer(const std::string& name, const std::vector<int>& data);
    void createBox(b2World& world, int startX, int startY, int countX, int countY) const;
};

