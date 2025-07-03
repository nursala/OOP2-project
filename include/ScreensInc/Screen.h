#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <Constants.h>
#include "ResourseInc/TextureManager.h"
#include "ScreensInc/Button.h"

//========================================================
// Abstract Screen class
// Base class for all screens (menu, help, etc).
// Manages background and UI buttons.
//========================================================
class Screen {
public:
    Screen();
    virtual ~Screen() = default;

    // Render background and buttons
    virtual void render(sf::RenderWindow& window);

    // Update button hover states
    virtual void update(sf::RenderWindow& window, float dt);

    // Handle input events (delegates to buttons)
    virtual void processEvent(sf::Event& event, sf::RenderWindow& window);

    // Access a specific button by ID
    Button& getButton(const Constants::ButtonID id);

    // Return the ID of the screen
    virtual Constants::ScreenID getScreenID() const = 0;

    // Initialize screen components (must override)
    virtual void init() = 0;

protected:
    // Set background texture
    void setBackGroundTexture(const Constants::TextureID texture);

    // Set up buttons from generic descriptions
    template <typename T = std::monostate>
    void setButtons(std::vector<Constants::GenericButton<T>>& info);

    // Hook to handle special info per button type (optional)
    virtual void handleExtraButtonInfo(Constants::ButtonID id) {}

    // Hook to create special/custom buttons (optional)
    virtual void setSpecialButtons() {}

    // Set background size (default = window size)
    virtual void setSize(const sf::Vector2f& size = {
        Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT });

    // Draw only the buttons (called by render)
    void drawButtons(sf::RenderWindow& window);

    sf::RectangleShape m_backGround; // Background rectangle
    std::vector<Constants::GenericButton<std::monostate>> m_generalButtons; // Default buttons
    std::unordered_map<Constants::ButtonID, Button> m_buttons; // ID-to-Button map
};

//-------------------------------------
// Set up buttons from generic descriptions
template <typename T>
void Screen::setButtons(std::vector<Constants::GenericButton<T>>& buttons) {
    for (auto& info : buttons) {
        auto& btn = m_buttons.emplace(
            info.id,
            Button(info.size, info.position, info.label)
        ).first->second;

        btn.setCommand(std::move(info.command));

        if (info.color.has_value())
            btn.setColor(info.color.value());

        if constexpr (!std::is_same_v<T, std::monostate>) {
            if (info.type.has_value())
                handleExtraButtonInfo(info.id);
        }
    }
}
