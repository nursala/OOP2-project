#include "HealthBar.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

HealthBar::HealthBar(float width, float height, int maxHealth)
	: Bar(width, height, sf::Color::Green,maxHealth)
{
}

void HealthBar::updateColor() {
    float ratio = (m_maxValue > 0) ? (m_currentValue / m_maxValue) : 0.f;
    if (ratio > 0.5f) {
        m_inner.setFillColor(sf::Color::Green);
    }
    else if (ratio > 0.2f) {
        m_inner.setFillColor(sf::Color::Yellow);
    }
    else {
        m_inner.setFillColor(sf::Color::Red);
    }
}