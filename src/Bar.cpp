#include "Bar.h"
#include <algorithm>

Bar::Bar(float width, float height, sf::Color color)
{
    m_maxValue = 100.f;
    m_currentValue = 100.f;

    m_border.setSize({ width, height });
    m_border.setFillColor(sf::Color(50, 50, 50, 200));
    m_border.setOutlineColor(sf::Color::Black);
    m_border.setOutlineThickness(1.f);
    m_border.setOrigin(width / 2, height / 2);

    m_inner.setSize({ width, height });
    m_inner.setFillColor(color);
    m_inner.setOrigin(width / 2, height / 2);
}

void Bar::setMaxValue(float maxValue) {
    m_maxValue = maxValue;
    updateBar();
}

void Bar::setValue(float value) {
    m_currentValue = std::max(0.f, std::min(value, m_maxValue));
    updateBar();
}

void Bar::setPosition(const sf::Vector2f& pos) {
    m_border.setPosition(pos);
    m_inner.setPosition(pos);
}

void Bar::draw(sf::RenderWindow& window) const {
    window.draw(m_inner);
    window.draw(m_border);
}

void Bar::updateBar() {
    float ratio = (m_maxValue > 0) ? (m_currentValue / m_maxValue) : 0.f;
    float width = m_border.getSize().x;
    m_inner.setSize({ width * ratio, m_border.getSize().y });
}
