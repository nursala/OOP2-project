#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "WeaponInc/Weapon.h"

//=====================================================
// Market screen
// Allows players to buy or equip weapons and shows
// available currency and weapon previews.
//=====================================================
class Market : public Screen {
public:
    // Constructor
    Market();

    // Default destructor
    ~Market() override = default;

    // Get screen identifier
    Constants::ScreenID getScreenID() const override;

    // Update the button labels based on weapon state
    void updateWeaponButtonLabels();

    // Render market elements and UI
    void render(sf::RenderWindow& window) override;

    // Set a temporary message text in the UI
    void setMessage(const std::string string);

    // Initialize market screen and buttons
    void init() override;

protected:
    // Handle additional info from weapon buttons
    void handleExtraButtonInfo(Constants::ButtonID id) override;
private:
    std::unordered_map<Constants::WeaponType, Button*> m_weaponButtons; // Mapping from weapon type to buttons
    std::vector<sf::RectangleShape> m_weaponImages;                     // Weapon image previews
    std::vector<Constants::GenericButton<Constants::WeaponType>> m_weaponButtonInfo; // Weapon button definitions

    std::pair<sf::RectangleShape, sf::Text> m_money; // Coin icon and money value text
    sf::Text m_messageText;                          // Message shown at top center
};
