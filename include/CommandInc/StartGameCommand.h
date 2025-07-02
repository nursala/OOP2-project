#pragma once
#include "CommandInc/Command.h"
#include "LevelManager.h"
#include "Controller.h"
#include "ScreensInc/PlayGround.h"
#include "ScreensInc/LoadGame.h"

class StartGameCommand : public Command 
{
public:
    StartGameCommand(Constants::LevelID level)
        : m_level(level) 
    {
    }

    void execute() override {  
       LevelManager::instance().loadLevel(m_level);  
       Controller::getInstance().pushScreen(std::make_unique<LoadGame>());
    }

private:
    Constants::LevelID m_level;
};