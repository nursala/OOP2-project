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

protected:
	//Constans::Constants::ScreenID m_screenID;
	void setBackGroundTexture(const Constants::TextureID texture);
	sf::RectangleShape m_backGround;
	//std::vector <Constants::ButtonInfo> m_buttonInfos;
	std::vector <Constants::GenericButton<>> m_generalButtons;
    template <typename T = std::monostate>  
    void setButtons(std::vector<Constants::GenericButton<T>>& buttons);
	template <typename T>
	void handleExtraButtonInfo(const Constants::GenericButton<T>&) {};
	std::unordered_map<Constants::ButtonID, Button> m_buttons;
};

template <typename T>
void Screen::setButtons(std::vector<Constants::GenericButton<T>>& buttons)
{
	for (auto& info : buttons)
	{
		auto& btn = m_buttons.emplace(
			info.id,
			Button(info.size, info.position, info.label)
		).first->second;

		btn.setCommand(std::move(info.command));

		if constexpr (!std::is_same_v<T, std::monostate>)
		{
			if (info.type.has_value())
				this->handleExtraButtonInfo<T>(info);
		}
	}
}

