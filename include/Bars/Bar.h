#pragma once

//======================================================
// Author:        [Your Name]
// ID:            [Your ID]
// Login:         [Your Login]
// Description:   Base class for all status bars (health, armor, etc.),
//                with update and rendering logic.
//======================================================

#include <SFML/Graphics.hpp>
#include <RenderLayers.h>

class Bar {
public:
    // Constructor to initialize the bar with size, color, and maximum value.
    Bar(const float width, const float height, const sf::Color& color, const float& maxValue);

    virtual ~Bar() = default;

    // Sets the maximum value of the bar.
    void setMaxValue(const float maxValue);

    // Sets the current value of the bar.
    void setValue(const float value);

    // Sets the position of the bar on screen.
    void setPosition(const sf::Vector2f& pos);

    // Draws the bar on the specified render layer.
    void draw(RenderLayers& renderLayers) const;

    // Returns the current value of the bar.
    float getValue() const { return m_currentValue; }

    // Returns the maximum value of the bar.
    float getMaxValue() const { return m_maxValue; }

    // Returns the outer border shape (for use in derived classes).
    const sf::RectangleShape& getBorder() const { return m_border; }

    // Pure virtual function to be implemented by derived classes to update the color.
    virtual void updateColor() = 0;

protected:
    float m_maxValue;                // The maximum value the bar can represent.
    float m_currentValue;           // The current value of the bar.
    sf::RectangleShape m_border;    // The outer frame of the bar.
    sf::RectangleShape m_inner;     // The filled inner part representing the current value.

private:
    // Updates the size of the filled inner bar based on the current value.
    void updateBar();
	float m_angle = 0.f; // Rotation angle in degrees
};
