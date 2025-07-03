#pragma once

#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

//==================================================
// GameWin - Screen displayed after winning the game.
// Shows a congratulatory message and return option.
//==================================================
class GameWin : public Screen {
public:
    GameWin();
    ~GameWin() override = default;

    // Initialize the screen: music + buttons
    void init() override;

    // Return screen ID (GameWin)
    Constants::ScreenID getScreenID() const override;
};
