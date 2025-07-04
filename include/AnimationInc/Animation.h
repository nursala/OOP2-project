#pragma once

#include <SFML/Graphics.hpp>

//======================================================
// Description:   This class handles sprite sheet animation,
//                changing the displayed texture area (UV) over time.
//======================================================

class Animation {
public:
    // Constructor: Initializes the animation with texture, image count, and switch time.
    Animation(const sf::Texture* texture, const sf::Vector2u& imageCount, const float switchTime);

    // Updates the animation frame based on deltaTime.
    void update(float deltaTime);

    // Resets the animation parameters (like constructor).
    void setAll(const sf::Texture* texture, const sf::Vector2u& imageCount, const float switchTime);

    // Returns the current rectangle to display from the texture.
    const sf::IntRect& getUvRect() const;

private:
    sf::Vector2u m_imageCount;    // Number of images in (columns, rows)
    sf::Vector2u m_currentImage;  // Current image being shown (x = col, y = row)
    float m_totalTime = 0.0f;     // Time accumulator since last switch
    float m_switchTime = 0.0f;    // Time between frames
    int m_totalImages = 1;        // Total number of frames in the sprite sheet
    int m_displayed = 0;          // Total frames displayed so far
    sf::IntRect m_uvRect;         // Rectangle area to draw (part of the texture)
};
