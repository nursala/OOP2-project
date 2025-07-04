#include "AnimationInc/Animation.h"
#include <cmath>
#include <iostream>

// Constructor: initializes the animation system.
Animation::Animation(const sf::Texture* texture, const sf::Vector2u& imageCount, const float switchTime)
    : m_imageCount(imageCount),
    m_switchTime(2.f / static_cast<float>(imageCount.x * imageCount.y)), // override switchTime to match total frames
    m_displayed(0),
    m_totalTime(0.0f),
    m_currentImage({ 0, 0 })
{
    if (texture) {
        m_uvRect.width = static_cast<int>(texture->getSize().x) / static_cast<int>(imageCount.x);
        m_uvRect.height = static_cast<int>(texture->getSize().y) / static_cast<int>(imageCount.y);
        update(0.0f); // Set initial frame
        m_totalImages = static_cast<int>(imageCount.x * imageCount.y - 1);
    }
}

// Updates the animation by advancing the frame according to deltaTime.
void Animation::update(float deltaTime)
{
    m_currentImage.y = static_cast<int>(std::floor(m_displayed / m_imageCount.x));
    m_totalTime += deltaTime;

    if (m_totalTime >= m_switchTime)
    {
        m_totalTime -= m_switchTime;
        m_displayed++;

        // Reset if all frames shown
        if (m_totalImages <= m_displayed)
        {
            m_displayed = 0;
            m_currentImage = { 0, 0 };
        }

        m_currentImage.x = (m_currentImage.x + 1) % m_imageCount.x;
        m_currentImage.y = (m_displayed / m_imageCount.x) % m_imageCount.y;
    }

    m_uvRect.top = static_cast<int>(m_currentImage.y * m_uvRect.height);
    m_uvRect.left = static_cast<int>(m_currentImage.x * m_uvRect.width);
}

// Resets the animation settings (like the constructor)
void Animation::setAll(const sf::Texture* texture, const sf::Vector2u& imageCount, const float switchTime)
{
    m_imageCount = imageCount;
    m_switchTime = 2.f / static_cast<float>(imageCount.x * imageCount.y);
    m_totalTime = 0.0f;
    m_currentImage = { 0, 0 };
    m_displayed = 0;
    m_totalImages = static_cast<int>(imageCount.x * imageCount.y);

    if (texture) {
        m_uvRect.width = static_cast<int>(texture->getSize().x) / static_cast<int>(imageCount.x);
        m_uvRect.height = static_cast<int>(texture->getSize().y) / static_cast<int>(imageCount.y);
    }
    else {
        m_uvRect = { 0, 0, 0, 0 };
    }
}

// Returns the current UV rectangle for the texture.
const sf::IntRect& Animation::getUvRect() const
{
    return m_uvRect;
}
