#pragma once

#include "ScreensInc/Screen.h"
#include <unordered_map>
#include <vector>
#include <string>
#include "WeaponInc/Weapon.h"

class Market : public Screen {
public:
    Market();
    ~Market() override = default;

    Constants::ScreenID getScreenID() const override;
    void render(sf::RenderWindow& window) override;
    void init() override;

    void setMessage(const std::string string);
    void updateWeaponButtonLabels();
    
protected:
 
private:
    std::unordered_map<Constants::WeaponType, Button*> m_weaponButtons;
    std::vector<Constants::GenericButton<Constants::WeaponType>> m_weaponButtonInfo;
    std::vector<sf::RectangleShape> m_weaponImages;
    std::pair<sf::RectangleShape, sf::Text> m_money;
    sf::Text m_messageText;
};
