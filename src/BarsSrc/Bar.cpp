#include "Bars/Bar.h"
#include "Controller.h"
#include <algorithm>

//======================================================
// Constructor: initializes the bar with size, color, and max value.
//======================================================
Bar::Bar(const float width, const float height, const sf::Color& color, const float& maxValue)
    : m_maxValue(maxValue), m_currentValue(maxValue)
{
    // Setup border rectangle
    m_border.setSize({ width, height });
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineColor(sf::Color::Black);
    m_border.setOutlineThickness(1.f);
    m_border.setOrigin(width / 2.f, height / 2.f);

    // Setup inner (filled) rectangle
    m_inner.setSize({ width, height });
    m_inner.setFillColor(color);
    m_inner.setOrigin(width / 2.f, height / 2.f);
}

//======================================================
// Sets the maximum value of the bar.
//======================================================
void Bar::setMaxValue(float maxValue) {
    m_maxValue = maxValue;
    updateBar();
}

//======================================================
// Sets the current value of the bar (clamped between 0 and max).
//======================================================
void Bar::setValue(float value) {
    m_currentValue = std::clamp(value, 0.f, m_maxValue);
    updateBar();
}

//======================================================
// Sets the position of both the border and inner rectangles.
//======================================================
void Bar::setPosition(const sf::Vector2f& pos) {
    m_border.setPosition(pos);
    m_inner.setPosition(pos);
}

//======================================================
// Draws the bar and the value text onto the render layer.
//======================================================
void Bar::draw(RenderLayers& renderLayers) const {
    renderLayers.drawForeground(m_inner);
    renderLayers.drawForeground(m_border);

    // Optional: draw numeric text on top of the bar.
    sf::Text text;
    text.setFont(Controller::getInstance().getFont());
    text.setString(
        std::to_string(static_cast<int>(m_currentValue)) + " / " +
        std::to_string(static_cast<int>(m_maxValue))
    );
    text.setCharacterSize(5);
    text.setFillColor(sf::Color::White);
    text.setPosition(
        m_border.getPosition().x - 10.f,
        m_border.getPosition().y - 3.f
    );
    renderLayers.drawForeground(text);
}

//======================================================
// Internal update of the filled inner size based on current value.
//======================================================
void Bar::updateBar() {
    const float ratio = (m_maxValue > 0.f) ? (m_currentValue / m_maxValue) : 0.f;
    const float width = m_border.getSize().x;
    m_inner.setSize({ width * ratio, m_border.getSize().y });

    updateColor();  // Let derived class choose color logic
}
