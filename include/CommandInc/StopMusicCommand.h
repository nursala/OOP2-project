#pragma once
#include "CommandInc/Command.h"
#include "ResourseInc/SoundManager.h"

class StopMusicCommand : public Command {
public:
    void execute() override { 
        SoundManager::instance().pause(SoundID::BackgroundMusic);
    };
};