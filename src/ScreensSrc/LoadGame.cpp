#include "ScreensInc/LoadGame.h"
#include "ResourseInc/SoundManger.h"
#include "ResourseInc/SoundManger.h"
#include "ScreensInc/Screen.h"
#include <CommandInc/PopToHomeCommand.h>

LoadGame::LoadGame()
{
	setBackGroundTexture(Constants::TextureID::GAMEWIN);
	setSize();
}

void LoadGame::init()
{
	m_generalButtons.clear();
	SoundManger::instance().play(Constants::SoundID::MENUMUSIC);
}

Constants::ScreenID LoadGame::getScreenID() const
{
	return Constants::ScreenID::GameWin;
}