#pragma once

#include "CommandInc/Command.h"
#include "ResourseInc/SoundManger.h"

class Button;
class StopMusicCommand;

class StartMusicCommand : public Command {
public:
	StartMusicCommand(Button& button) : m_button(button) {}
	void execute() override;
private:
	Button& m_button;
};