#include "CommandInc/StopMusicCommand.h"
#include "CommandInc/StartMusicCommand.h"
#include "ScreensInc/Button.h"

void StopMusicCommand::execute() {
	SoundManger::instance().mute(true, false);
	m_button.setTexture(Constants::TextureID::SOUNDOFF);
	m_button.setCommand(std::make_unique<StartMusicCommand>(m_button));
}