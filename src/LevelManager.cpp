#include "LevelManager.h"

//-------------------------------------
//LevelManager Singleton Implementation
LevelManager& LevelManager::instance() {
    static LevelManager instance;
    return instance;
}

//-------------------------------------
// Constructor
LevelManager::LevelManager() {
    m_levelFiles = {
        { Constants::LevelID::EasyMap,   "easy_map.json" },
        { Constants::LevelID::MediumMap, "medium_map.json" },
        { Constants::LevelID::HardMap,   "hard_map.json" }
    };
}

//-------------------------------------
// Load level files
bool LevelManager::loadLevel(const Constants::LevelID levelID) {
    auto it = m_levelFiles.find(levelID);
    if (it != m_levelFiles.end()) {
        m_currentLevel = it->first;
        return true;
    }
    throw std::runtime_error("Level not found");
}

//-------------------------------------
// Get the path of the current level
const std::string& LevelManager::getCurrentLevelPath() const {
    auto it = m_levelFiles.find(m_currentLevel);
    if (it == m_levelFiles.end())
        throw std::runtime_error("Current level not found");
    return it->second;
}

//-------------------------------------
// Get the current level ID
const Constants::LevelID LevelManager::getCurrentLevel() const {
    return m_currentLevel;
}
