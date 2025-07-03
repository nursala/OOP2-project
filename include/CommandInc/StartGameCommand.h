#pragma once

#include "CommandInc/Command.h"
#include "LevelManager.h"
#include "Controller.h"
#include "ScreensInc/PlayGround.h"
#include "ScreensInc/LoadGame.h"

// -----------------------------
// StartGameCommand - loads a level and pushes LoadGame screen
// -----------------------------
class StartGameCommand : public Command {
public:
    StartGameCommand(Constants::LevelID level);
    void execute() override;

private:
    Constants::LevelID m_level;
};
