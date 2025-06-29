#include "Bar.h"
#include "Controller.h"
#include <algorithm>

Bar::Bar(float width, float height, sf::Color color,float maxValue)
{
    m_maxValue = maxValue;
    m_currentValue = maxValue;

    m_border.setSize({ width, height });
    m_border.setFillColor(sf::Color::Transparent);
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
   /* window.draw(m_inner);
    window.draw(m_border);

        sf::Text text;
        text.setFont(m_font);
        text.setString(
            std::to_string(static_cast<int>(m_currentValue)) + " / " +
			std::to_string(static_cast<int>(m_maxValue))
        );
        text.setCharacterSize(5);
        text.setFillColor(sf::Color::White);
        text.setPosition(m_border.getPosition().x - 10.f,
            m_border.getPosition().y - 3.f);
        window.draw(text);*/
}

void Bar::draw(RenderLayers& renderLayers) const {
    renderLayers.drawForeground(m_inner);
    renderLayers.drawForeground(m_border);

    sf::Text text;
    text.setFont(Controller::getInstance().getFont());
    text.setString(
        std::to_string(static_cast<int>(m_currentValue)) + " / " +
        std::to_string(static_cast<int>(m_maxValue))
    );
    text.setCharacterSize(5);
    text.setFillColor(sf::Color::White);
    text.setPosition(m_border.getPosition().x - 10.f, m_border.getPosition().y - 3.f);
    renderLayers.drawForeground(text);
}


void Bar::updateBar() {
    float ratio = (m_maxValue > 0) ? (m_currentValue / m_maxValue) : 0.f;
    float width = m_border.getSize().x;
    m_inner.setSize({ width * ratio, m_border.getSize().y });
    updateColor();
}

