#pragma once

#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

//==================================================
// GameOver - Screen displayed after the player loses.
// Allows returning to home.
//==================================================
class GameOver : public Screen {
public:
    GameOver();
    ~GameOver() override = default;

    // Initialize buttons and music
    void init() override;

    // Return screen ID (GameOver)
    Constants::ScreenID getScreenID() const override;
};
