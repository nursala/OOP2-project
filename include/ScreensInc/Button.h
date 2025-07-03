#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "CommandInc/Command.h"
#include "Constants.h"

//==================================================
// Button - Represents an interactive UI button
// Supports texture, color, text, hover effect, and command execution.
//==================================================
class Button {
public:
    // Constructor: create button with size, position, and optional text
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text = "");

    // Set the fill color (used for visual theming)
    void setColor(const sf::Color color);

    // Set the command to be executed when clicked
    void setCommand(std::unique_ptr<Command> command);

    // Set texture for the button shape
    void setTexture(const Constants::TextureID textureID);

    // Check mouse hover state and apply visual feedback
    void updateHover(const sf::RenderWindow& window);

    // Draw the button and text
    void render(sf::RenderWindow& window);

    // Handle mouse click events and trigger command
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    // Set button text and center it
    void setText(const std::string& text);

    // Execute command programmatically (without user click)
    void execute();

private:
    // Center the text inside the button shape
    void centerText();

    sf::RectangleShape m_shape;               // Visual shape of button
    sf::Text m_text;                          // Button label
    std::unique_ptr<Command> m_command;       // Associated command (action)
    sf::Color m_changingColor;                // Stored color for hover restore
    bool m_isColored = false;                 // Whether a custom color is used
};
