#pragma once

#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

//==================================================
// ChooseLevelScreen - Screen for selecting difficulty level
// Displays level buttons and map preview for each.
//==================================================
class ChooseLevelScreen : public Screen {
public:
    ChooseLevelScreen();
    ~ChooseLevelScreen() override = default;

    // Initialize the level buttons and map previews
    void init() override;

    // Return screen ID (ChooseLevel)
    Constants::ScreenID getScreenID() const override;

    // Draw background, buttons, and level images
    void render(sf::RenderWindow& window) override;

private:
    std::vector<sf::RectangleShape> m_level; // Preview images for each level
};
