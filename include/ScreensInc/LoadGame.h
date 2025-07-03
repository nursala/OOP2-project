#pragma once

#include "ScreensInc/Screen.h"
#include "Constants.h"

// -----------------------------
// LoadGame - loading screen shown before gameplay starts
// -----------------------------
class LoadGame : public Screen {
public:
    // Constructor
    LoadGame();

    // Default destructor
    virtual ~LoadGame() = default;

    // Called when screen is shown - plays loading sound
    void init() override;

    // Updates the countdown timer and pushes the PlayGround screen
    void update(sf::RenderWindow& window, float dt) override;

    // Returns screen ID
    Constants::ScreenID getScreenID() const override;

private:
    float m_timer; // Countdown timer before transitioning to gameplay
};