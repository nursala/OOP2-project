#pragma once

#include <SFML/Graphics.hpp>
#include <Statusbar.h>
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"
#include "WorldInc/World.h"

//=====================================================
// PlayGround screen
// Represents the main gameplay screen containing
// the player, enemies, world logic, and status bar.
//=====================================================

class PlayGround : public Screen {
public:
    // Constructor
    PlayGround();

    // Default destructor
    virtual ~PlayGround() = default;

    // Update world logic and screen each frame
    virtual void update(sf::RenderWindow& window, float dt) override;

    // Render all world elements and UI
    void render(sf::RenderWindow& window) override;

    // Return screen identifier
    Constants::ScreenID getScreenID() const override;

    void setIniSound();

    void setSound(Constants::SoundID sound, float volume);

    // Initialize screen (called when first displayed)
    void init() override;

protected:
    // Add special screen-specific buttons
    void setSpecialButtons() override;

private:
    sf::View m_view;       // View for scrolling the map
    World m_world;         // Core game world
    Statusbar m_statusBar; // Status bar display
};
