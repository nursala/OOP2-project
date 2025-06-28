#include "AnimationInc/Animation.h"
#include <cmath>
#include <iostream>
Animation::Animation(const sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	: m_imageCount(imageCount), m_switchTime(switchTime), m_displayed(0), m_totalImages(0) {

	m_totalTime = 0.0f;
	m_currentImage.x = 0;

	if (texture) {
		m_uvRect.width = texture->getSize().x / static_cast<int>(imageCount.x);
		m_uvRect.height = texture->getSize().y / static_cast<int>(imageCount.y);

		update(1, 1, 0.0f); // Initialize with row 1 and total images 1
	}
}

void Animation::update(int row, int totalImages, float deltaTime)
{
	//std::cout << "Updating animation with row = " << row << " deltaTime = " << deltaTime << "\n";

	m_totalImages = totalImages - 1;
	m_currentImage.y = (row - 1) + static_cast<int>(std::floor(m_displayed / m_imageCount.x));
	m_totalTime += deltaTime;

	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		m_currentImage.x++;
		m_displayed++;

		if (m_currentImage.x >= m_imageCount.x)
		{
			m_currentImage.x = 0;
		}

		if (m_totalImages < m_displayed)
		{
			m_displayed = 0;
			m_currentImage.x = 0;
			m_currentImage.y = row - 1;
		}
	}

	m_uvRect.top = m_currentImage.y * m_uvRect.height;
}

const sf::IntRect& Animation::getUvRect() const
{
	return m_uvRect;
}
