#pragma once

#include "ScreensInc/Screen.h"

//==================================================
// Help - Scrollable screen displaying game instructions.
//==================================================
class Help : public Screen {
public:
    Help();
    ~Help() override = default;

    // Initialize buttons and scroll settings
    void init() override;

    // Handle events including scroll and arrow keys
    void processEvent(sf::Event& event, sf::RenderWindow& window) override;

    // Render the help content with scrollable view
    void render(sf::RenderWindow& window) override;

    // Return screen ID (Help)
    Constants::ScreenID getScreenID() const override;

private:
    sf::View m_view;            // View for scrolling
    float m_scrollSpeed = 50.f; // Scroll sensitivity

    // Clamp view to prevent scrolling past background
    void clampView();
};
