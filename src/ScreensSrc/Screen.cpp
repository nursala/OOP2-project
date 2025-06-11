#include "ScreensInc/Screen.h"
#include "ResourseInc/TextureManager.h"

Screen::Screen()
{
	m_backGround.setSize(sf::Vector2f(1300, 1000));
	m_backGround.setPosition(0.0f, 0.0f);
}

void Screen::setBackGroundTexture(const TextureID texture)
{
	m_backGround.setTexture(TextureManager::instance().get(texture));
	m_backGround.setTextureRect(sf::IntRect(0, 0,
		TextureManager::instance().get(texture)->getSize().x,
		TextureManager::instance().get(texture)->getSize().y));
}

void Screen::setScreenAction(std::function<void(ScreenID)> action)
{
	m_changeScreen = std::move(action);
	init();
}

void Screen::render(sf::RenderWindow& window)
{
	window.draw(m_backGround);
	for (auto& [id, button] : m_buttons)
	{
		button.render(window);
	}
}

void Screen::update(sf::RenderWindow& window, float dt)
{
	(void)dt; // Placeholder for delta time, if needed in future
	for (auto& [id, button] : m_buttons)
	{
		button.updateHover(window);
	}
}

void Screen::processEvent(sf::Event& event, sf::RenderWindow& window)
{
	for (auto& [id, button] : m_buttons)
	{
		button.handleEvent(event, window);
	}
}