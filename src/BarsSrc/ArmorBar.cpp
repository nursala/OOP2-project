#include "Bars/ArmorBar.h"

//======================================================
// Constructor: initializes armor bar with size and max armor value.
// The initial color is set to blue.
//======================================================
ArmorBar::ArmorBar(const float width, const float height, const float maxArmor)
    : Bar(width, height, sf::Color::Blue, maxArmor)
{
}

//======================================================
// updateColor: adjusts fill color based on remaining armor ratio.
// > 0.5  = solid blue
// > 0.2  = light blue
// <= 0.2 = very light blue
//======================================================
void ArmorBar::updateColor()
{
    const float ratio = (m_maxValue > 0.f) ? (m_currentValue / m_maxValue) : 0.f;

    if (ratio > 0.5f)
        m_inner.setFillColor(sf::Color::Blue);
    else if (ratio > 0.2f)
        m_inner.setFillColor(sf::Color(0, 0, 255, 128)); // Light blue
    else
        m_inner.setFillColor(sf::Color(0, 0, 255, 64));  // Very light blue
}
