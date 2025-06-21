#include "ArmorBar.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

ArmorBar::ArmorBar(float width, float height, int maxArmor)
	: Bar(width, height, sf::Color::Blue, maxArmor)
{
}

void ArmorBar::updateColor()
{
	float ratio = (m_maxValue > 0) ? (m_currentValue / m_maxValue) : 0.f;
	if (ratio > 0.5f) {
		m_inner.setFillColor(sf::Color::Blue);
	}
	else if (ratio > 0.2f) {
		m_inner.setFillColor(sf::Color(0, 0, 255, 128)); // Light blue
	}
	else {
		m_inner.setFillColor(sf::Color(0, 0, 255, 64)); // Very light blue
	}
}
