#include "ScreensInc/LoadGame.h"
#include "ScreensInc/PlayGround.h"
#include "ResourseInc/SoundManger.h"
#include "ResourseInc/SoundManger.h"
#include "ScreensInc/Screen.h"
#include <CommandInc/PopToHomeCommand.h>
#include <CommandInc/PushScreenCommand.h>
#include <CommandInc/PopScreenCommand.h>


LoadGame::LoadGame()
{
	m_timer = 5.f;
	setBackGroundTexture(Constants::TextureID::GAMEWIN);
	setSize();
}

void LoadGame::init()
{
	m_generalButtons.clear();
	SoundManger::instance().play(Constants::SoundID::MENUMUSIC);
}

void LoadGame::update(sf::RenderWindow& window, float dt)
{
	Screen::update(window, dt);
	m_timer -= dt;
	if (m_timer <= 0.f)
	{
		auto command = PushScreenCommand<PlayGround>();
		auto popcommand = PopScreenCommand();
		popcommand.execute();
		command.execute();

	}
}

Constants::ScreenID LoadGame::getScreenID() const
{
	return Constants::ScreenID::GameWin;
}