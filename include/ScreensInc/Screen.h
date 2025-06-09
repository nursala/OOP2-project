#pragma once
#include <SFML/Graphics.hpp>
#include "ResourseInc/TextureManager.h"
#include "ScreensInc/Button.h"

enum class ScreenID {
	Home,
	Settings,
	Game,
	GameOver,
};


class Screen
{
public:
	Screen();
	virtual ~Screen() = default;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void update(sf::RenderWindow& window) = 0;
	virtual void processEvent(sf::Event& event, sf::RenderWindow& window) = 0;
	//ScreenID getScreenID() const;
	void setScreenAction(std::function<void(ScreenID)> action);
protected:
	//ScreenID m_screenID;
	void setBackGroundTexture(const TextureID texture);
	sf::RectangleShape m_backGround;
	std::unordered_map<ButtonID, Button> m_buttons;
	std::function<void(ScreenID)> m_changeScreen;
};
