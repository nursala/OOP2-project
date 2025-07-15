#pragma once

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "ResourseInc/BaseResourceManager.h"

class LevelManager 
{
public:

    static LevelManager& instance();

    bool loadLevel(const Constants::LevelID levelID);
    const std::string& getCurrentLevelPath() const;
    const Constants::LevelID getCurrentLevel() const;

private:
    LevelManager();
    LevelManager(const LevelManager&) = delete;
    LevelManager& operator=(const LevelManager&) = delete;

    Constants::LevelID m_currentLevel;
    std::unordered_map<Constants::LevelID, std::string> m_levelFiles;
};
