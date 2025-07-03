#pragma once

#include "CommandInc/Command.h"
#include "ResourseInc/SoundManger.h"

class Button;
// -----------------------------
// StopMusicCommand - stops the music
// -----------------------------
class StopMusicCommand : public Command {
public:
    StopMusicCommand(Button& button);
    void execute() override;

private:
    Button& m_button;
};
