#include "AnimationInc/Animation.h"
#include <cmath>
#include <iostream>
Animation::Animation(const sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	: m_imageCount(imageCount), m_switchTime(switchTime), m_displayed(0) {

	m_totalTime = 0.0f;
	m_currentImage.x = 0;

	if (texture) {
		m_uvRect.width = texture->getSize().x / static_cast<int>(imageCount.x);
		m_uvRect.height = texture->getSize().y / static_cast<int>(imageCount.y);

		update(1, 0.0f); // Initialize with row 1 and total images 1
		m_totalImages = imageCount.x * imageCount.y - 1; // Total images based on image count
	}
}

void Animation::update(int row, float deltaTime)
{
	//std::cout << "Updating animation with row = " << row << " deltaTime = " << deltaTime << "\n";

	//m_totalImages--;
	//if (m_totalImages == 21 || m_totalImages == 9)
	//m_totalImages--;
	m_currentImage.y = static_cast<int>(std::floor(m_displayed / m_imageCount.x));
	m_totalTime += deltaTime;
	//std::cout << "current Time: " << m_totalTime << " switchTime: " << m_switchTime << std::endl;
	if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		m_displayed++;
		std::cout << "displayed: " << m_displayed << "totalImages: " << m_totalImages << std::endl;
		std::cout << "rows: " << m_currentImage.y << std::endl;
		std::cout << "columns: " << m_currentImage.x << std::endl;


		if (m_currentImage.x + 1 >= m_imageCount.x)
		{
			m_currentImage.x = 0;
		}

		if (m_currentImage.y + 1 >= m_imageCount.y)
		{
			m_currentImage.y = 0;
		}

		if (m_totalImages <= m_displayed)
		{
			m_displayed = 0;
			m_currentImage.x = 0;
			m_currentImage.y = 0;
		}
		m_currentImage.x++;
	}

	m_uvRect.top = m_currentImage.y * m_uvRect.height;
}


void Animation::setAll(const sf::Texture* texture,sf::Vector2u imageCount, float switchTime, float deltaTime)
{

	m_switchTime = switchTime;
	m_imageCount = imageCount;

	m_totalTime = 0.0f;
	m_currentImage.x = 0;
	m_displayed = 0; 

	if (texture) {
		m_uvRect.width = texture->getSize().x / static_cast<int>(imageCount.x);
		m_uvRect.height = texture->getSize().y / static_cast<int>(imageCount.y);
	}
	else {
		m_uvRect.width = 0;
		m_uvRect.height = 0;
	}
	m_totalImages = imageCount.x * imageCount.y - 1;
	//update(1, imageCount.x * imageCount.y, deltaTime); // Initialize with row 1 and total images 1
}

const sf::IntRect& Animation::getUvRect() const
{
	return m_uvRect;
}
