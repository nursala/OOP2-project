#include "Bars/HealthBar.h"

//======================================================
// Constructor: initializes health bar with size and max health value.
// The initial color is set to green.
//======================================================
HealthBar::HealthBar(const float width, const float height, const float maxHealth)
    : Bar(width, height, sf::Color::Green, maxHealth)
{
}

//======================================================
// updateColor: adjusts fill color based on remaining health ratio.
// > 0.5  = green
// > 0.2  = yellow
// <= 0.2 = red
//======================================================
void HealthBar::updateColor()
{
    const float ratio = (m_maxValue > 0.f) ? (m_currentValue / m_maxValue) : 0.f;

    if (ratio > 0.5f)
        m_inner.setFillColor(sf::Color::Green);
    else if (ratio > 0.2f)
        m_inner.setFillColor(sf::Color::Yellow);
    else
        m_inner.setFillColor(sf::Color::Red);
}
