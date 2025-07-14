#include "LoadMap.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
constexpr float SCALE = 30;

//-------------------------------------
// LoadMap Constructor
LoadMap::LoadMap(const std::string& jsonPath)
{
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open map file: " + jsonPath);
    }

    json j;
    file >> j;

    m_width = j["width"];
    m_height = j["height"];
    m_tileWidth = j["tilewidth"];
    m_tileHeight = j["tileheight"];

    for (const auto& layer : j["layers"]) {
        std::string name = layer["name"];
        std::vector<int> tiles = layer["data"].get<std::vector<int>>();
        addLayer(name, tiles);
    }
    if (m_layers.empty()) {
        throw std::runtime_error("No layers found in the map JSON file");
    }

    parseSpawnLayer("Spawns", 82, 253, 181);
    if (m_enemySpawns.empty() || m_giftSpawns.empty()) {
        throw std::runtime_error("No spawn points found in the map JSON file");
    }
}

//-------------------------------------
// Creates collision objects for a specified layer
void LoadMap::createCollisionObjects(b2World& world, const std::string& layerName) 
{
    for (const auto& layer : m_layers) {
        if (layer.name != layerName)
            continue;

        std::vector<std::vector<bool>> visited(m_height, std::vector<bool>(m_width, false));

        for (int y = 0; y < m_height; ++y) {
            for (int x = 0; x < m_width; ++x) {
                if (visited[y][x])
                    continue;

                int tile = layer.tiles[y * m_width + x];
                if (tile <= 0)
                    continue;

                int maxWidth = 1;
                int maxHeight = 1;

                while (x + maxWidth < m_width &&
                    layer.tiles[y * m_width + (x + maxWidth)] > 0 &&
                    !visited[y][x + maxWidth]) {
                    ++maxWidth;
                }

                bool canExtend = true;
                while (y + maxHeight < m_height && canExtend) {
                    for (int i = 0; i < maxWidth; ++i) {
                        if (layer.tiles[(y + maxHeight) * m_width + (x + i)] <= 0 ||
                            visited[y + maxHeight][x + i]) {
                            canExtend = false;
                            break;
                        }
                    }

                    if (canExtend)
                        ++maxHeight;
                }

                for (int dy = 0; dy < maxHeight; ++dy) {
                    for (int dx = 0; dx < maxWidth; ++dx) {
                        visited[y + dy][x + dx] = true;
                    }
                }

                createBox(world, x, y, maxWidth, maxHeight);
            }
        }

        break;
    }
}

//-------------------------------------
// Creates a single static collision box in the world
void LoadMap::createBox(b2World& world, const int startX, const int startY, const int countX, const int countY) const {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(
        ((startX + countX / 2.0f) * m_tileWidth) / SCALE,
        ((startY + countY / 2.0f) * m_tileHeight) / SCALE
    );
    b2PolygonShape shape;
    shape.SetAsBox(
        (countX * m_tileWidth) / 2.0f / SCALE,
        (countY * m_tileHeight) / 2.0f / SCALE
    );
    b2Body* body = world.CreateBody(&bodyDef);
    body->CreateFixture(&shape, 0.0f);
}

//-------------------------------------
// Parses a spawn layer and collects spawn positions for different entity types
void LoadMap::parseSpawnLayer(const std::string& layerName, const int playerTile, const int enemyTile, const int giftTile) {
    for (const auto& layer : m_layers) {
        if (layer.name == layerName) {
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    int index = y * m_width + x;
                    int tile = layer.tiles[index];
                    sf::Vector2f pos(static_cast<float>(x * m_tileWidth), static_cast<float>(y * m_tileHeight));

                    if (tile == playerTile) {
						m_playerSpawn = pos; // Assuming only one player spawn
                    }
                    else if (tile == enemyTile) {
                        m_enemySpawns.push_back(pos);
                    }
                    else if (tile == giftTile) {
                        m_giftSpawns.push_back(pos);
                    }
                }
            }
            break;
        }
    }
}

//-------------------------------------
// Returns the spawn positions of players
const sf::Vector2f LoadMap::getPlayerSpawns() const {
    return m_playerSpawn;
}

//  -------------------------------------
// Returns the spawn positions of enemies
const std::vector<sf::Vector2f>& LoadMap::getEnemySpawns() const {
    return m_enemySpawns;
}

//-------------------------------------
// Returns the spawn positions of gifts
const std::vector<sf::Vector2f>& LoadMap::getGiftSpawns() const {
    return m_giftSpawns;
}

//-------------------------------------
// Adds a new layer to the map
void LoadMap::addLayer(const std::string& name, const std::vector<int>& data) {
    m_layers.push_back({ name, data });
}

//-------------------------------------
// Checks if a tile at the specified coordinates is walkable
bool LoadMap::isWalkable(const int x, const int y) const {
    for (const auto& layer : m_layers) {
        if (layer.name == "walls") {
            int index = y * m_width + x;
            if (index >= 0 && index < layer.tiles.size()) {
                return layer.tiles[index] == 0;
            }
        }
    }
    return false;
}