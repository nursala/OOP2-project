#include "ScreensInc/LoadGame.h"
#include "ScreensInc/PlayGround.h"
#include "ResourseInc/SoundManager.h"
#include "ResourseInc/SoundManager.h"
#include "ScreensInc/Screen.h"
#include <CommandInc/PopToHomeCommand.h>
#include <CommandInc/PushScreenCommand.h>
#include <CommandInc/PopScreenCommand.h>
#include <memory>

// -----------------------------
// LoadGame - implementation of loading screen logic
// -----------------------------

LoadGame::LoadGame()
{
	m_timer = 5.f;
	setBackGroundTexture(Constants::TextureID::LOADGAME);
	setSize();
	m_animation = std::make_unique<Animation>(TextureManager::instance().get(Constants::TextureID::HANDGUNMOVE), sf::Vector2u(7, 3), 0.4f);
	m_sprite.setTexture(*TextureManager::instance().get(Constants::TextureID::HANDGUNMOVE));
	m_sprite.setTextureRect(m_animation->getUvRect());
	m_sprite.setOrigin(m_animation->getUvRect().width / 2.f, m_animation->getUvRect().height / 2.f);
	m_sprite.setScale(0.5f, 0.5f);
}

// Initializes the screen (stops menu music and plays loading music)
void LoadGame::init()
{
    m_generalButtons.clear();
    SoundManager::instance().stop(Constants::SoundID::MENUMUSIC);
    SoundManager::instance().play(Constants::SoundID::MATCHMAKINGMUSIC);
    SoundManager::instance().setVolume(Constants::SoundID::MATCHMAKINGMUSIC, 40.f);
}

// Updates countdown timer and transitions to PlayGround screen
void LoadGame::update(sf::RenderWindow& window, float dt)
{
	Screen::update(window, dt);
	m_animation->update(dt);
	m_sprite.setPosition(sf::Vector2f(Constants::WINDOW_WIDTH * 0.85f, Constants::WINDOW_HEIGHT * 0.88f));
	m_sprite.setTextureRect(m_animation->getUvRect());
	m_sprite.setRotation(m_sprite.getRotation() + 20.f * dt * 5.0f);
	m_timer -= dt;
	if (m_timer <= 0.f)
	{
		auto command = PushScreenCommand<PlayGround>();
		//auto popcommand = PopScreenCommand();
		//popcommand.execute();
		command.execute();
	}
}

// Returns screen ID for LoadGame
Constants::ScreenID LoadGame::getScreenID() const
{
	return Constants::ScreenID::LoadGame;
}

void LoadGame::render(sf::RenderWindow& window)
{
	Screen::render(window);
	window.draw(m_sprite);
}
