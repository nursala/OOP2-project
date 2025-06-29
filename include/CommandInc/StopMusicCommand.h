#pragma once
#include "CommandInc/Command.h"
#include "ResourseInc/SoundManger.h"

class StopMusicCommand : public Command {
public:
    void execute() override { 
        SoundManger::instance().pause(Constants::SoundID::BackgroundMusic);
    };
};