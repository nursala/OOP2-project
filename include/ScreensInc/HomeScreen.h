#pragma once

#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

//==================================================
// HomeScreen - Main menu screen of the game.
// Displays buttons for Play, Market, Help, and Exit.
//==================================================
class HomeScreen : public Screen {
public:
    HomeScreen();
    ~HomeScreen() override = default;

    // Initialize the screen: buttons, music, etc.
    void init() override;

    // Return the screen ID (Home)
    Constants::ScreenID getScreenID() const override;
};
