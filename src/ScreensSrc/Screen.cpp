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

//ScreenID Screen::getScreenID() const
//{
//	/*return m_screenID;*/
//}

void Screen::setScreenAction(std::function<void(ScreenID)> action)
{
	m_changeScreen = std::move(action); 
}