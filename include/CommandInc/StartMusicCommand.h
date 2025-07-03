#pragma once

#include "CommandInc/Command.h"
#include "ResourseInc/SoundManger.h"

class Button;

// -----------------------------
// StartMusicCommand - starts playing background music
// -----------------------------
class StartMusicCommand : public Command {
public:
    StartMusicCommand(Button& button);
    void execute() override;

private:
    Button& m_button;
};
