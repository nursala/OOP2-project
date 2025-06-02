#include "LoadMap.h"
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
constexpr float SCALE = 30.f; // 1 متر = 30 بكسل

// Constructor initializes map dimensions and tile sizes
LoadMap::LoadMap(const std::string& jsonPath) {
    std::ifstream file(jsonPath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open JSON map file");
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
    

}

// Creates collision objects for a specified layer
void LoadMap::createCollisionObjects(b2World& world, const std::string& layerName) {
    for (const auto& layer : m_layers) {
        if (layer.name == layerName) {
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    int tile = layer.tiles[y * m_width + x];
                    if (tile > 0) {
                        createBox(world, x, y, 1, 1);
                    }
                }
            }
            break;
        }
    }
}



// Creates a single static collision box in the world
void LoadMap::createBox(b2World& world, int startX, int startY, int countX, int countY) const {
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

// Parses a spawn layer and collects spawn positions for different entity types
void LoadMap::parseSpawnLayer(const std::string& layerName, int playerTile, int enemyTile, int giftTile) {
    for (const auto& layer : m_layers) {
        if (layer.name == layerName) {
            for (int y = 0; y < m_height; ++y) {
                for (int x = 0; x < m_width; ++x) {
                    int index = y * m_width + x;
                    int tile = layer.tiles[index];
                    sf::Vector2f pos(static_cast<float>(x * m_tileWidth), static_cast<float>(y * m_tileHeight));

                    if (tile == playerTile) {
                        m_playerSpawns.push_back(pos);
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

// Returns the spawn positions of players
const std::vector<sf::Vector2f>& LoadMap::getPlayerSpawns() const {
    return m_playerSpawns;
}

// Returns the spawn positions of enemies
const std::vector<sf::Vector2f>& LoadMap::getEnemySpawns() const {
    return m_enemySpawns;
}

// Returns the spawn positions of gifts
const std::vector<sf::Vector2f>& LoadMap::getGiftSpawns() const {
    return m_giftSpawns;
}
void LoadMap::addLayer(const std::string& name, const std::vector<int>& data) {
    m_layers.push_back({ name, data });
}
