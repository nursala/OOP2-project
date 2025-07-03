#include "CommandInc/StartGameCommand.h"

StartGameCommand::StartGameCommand(Constants::LevelID level)
    : m_level(level) {
}

void StartGameCommand::execute() {
    LevelManager::instance().loadLevel(m_level);
    Controller::getInstance().pushScreen(std::make_unique<LoadGame>());
}
