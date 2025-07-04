#include "CommandInc/StartMusicCommand.h"
#include "CommandInc/StopMusicCommand.h"
#include "ScreensInc/Button.h"
#include "ScreensInc/Screen.h"

StartMusicCommand::StartMusicCommand(Button& button) : m_button(button)
{
}

void StartMusicCommand::execute() {
	SoundManager::instance().unmute(true, false);
	m_button.setTexture(Constants::TextureID::SOUNDON);
	m_button.setCommand(std::make_unique<StopMusicCommand>(m_button));
}