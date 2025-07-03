#pragma once

#include "ScreensInc/Screen.h"
#include "Constants.h"

// -----------------------------
// PauseScreen - derived screen for pausing gameplay
// -----------------------------
class PauseScreen : public Screen {
public:
    // Constructor
    PauseScreen();

    // Return the screen ID (Pause)
    virtual Constants::ScreenID getScreenID() const override;

    // Initialize buttons and pause background music
    virtual void init() override;
};
