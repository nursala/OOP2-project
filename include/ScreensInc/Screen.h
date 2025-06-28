#pragma once
#include <SFML/Graphics.hpp>
#include "ResourseInc/TextureManager.h"
#include "ScreensInc/Button.h"
#include <Constants.h>

class Screen
{
public:
	Screen();
	virtual ~Screen() = default;
	virtual void render(sf::RenderWindow& window);
	virtual void update(sf::RenderWindow& window, float dt);
	virtual void processEvent(sf::Event& event, sf::RenderWindow& window);
	void drawButtons(sf::RenderWindow& window);
	virtual void customizeProcessEvent() {};
	virtual Constants::ScreenID getScreenID() const = 0;
	virtual void init() = 0;
	virtual void setSize(const sf::Vector2f& size =
						{ Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT });
	void setButtons();
protected:
	//Constans::Constants::ScreenID m_screenID;
	void setBackGroundTexture(const Constants::TextureID texture);
	sf::RectangleShape m_backGround;
	std::vector <Constants::ButtonInfo> m_buttonInfos;
	std::unordered_map<Constants::ButtonID, Button> m_buttons;
};
