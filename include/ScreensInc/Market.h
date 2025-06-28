#pragma once

#include <SFML/Graphics.hpp>
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "WeaponInc/Weapon.h"

class Market : public Screen
{
public:
	Market();
	~Market() override = default;
	Constants::ScreenID getScreenID() const override;
	void updateWeaponButtonLabels();
	void render(sf::RenderWindow& window) override;
	void setMessage(const std::string string);
protected:
	void init() override;
private:
	std::unordered_map<Constants::WeaponType, std::pair<sf::RectangleShape, Button*>> m_weaponButtons;
	std::vector <Constants::WeaponButtonInfo> m_weaponButtonInfo;
	void setShapes();
	std::pair<sf::RectangleShape, sf::Text> m_money;
	sf::Text m_messageText;
};
