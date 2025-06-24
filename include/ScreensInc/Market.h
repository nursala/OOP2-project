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
	ScreenID getScreenID() const override;
	void updateWeaponButtonLabels();
	void render(sf::RenderWindow& window) override;
	void setMessage(const std::string string);
protected:
	void init() override;

private:
	std::unordered_map<WeaponType, Button*> m_weaponButtons;
	sf::Text m_moneyText;
	sf::Text m_messageText;
};
