#pragma once

#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"
#include "AnimationInc/Animation.h"

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
	// Renders the loading animation
    void render(sf::RenderWindow& window) override;
private:
	float m_timer; // Countdown timer before transitioning to gameplay
	std::unique_ptr<Animation> m_animation; // Animation for the character
	sf::Sprite m_sprite; // Sprite for the character
};