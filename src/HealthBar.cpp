#include "HealthBar.h"
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

HealthBar::HealthBar(float width, float height, int maxHealth, int maxArmor)
    : m_healthBar(width, height, sf::Color::Green),
    m_armorBar(width, height, sf::Color::Blue)
{
    m_healthBar.setMaxValue(maxHealth);
    m_healthBar.setValue(maxHealth);

    m_armorBar.setMaxValue(maxArmor);
    m_armorBar.setValue(maxArmor);
}

void HealthBar::setMaxHealth(float maxHealth) {
    m_healthBar.setMaxValue(maxHealth);
}

void HealthBar::setHealth(float health) {
    m_healthBar.setValue(health);
}

void HealthBar::setMaxArmor(float maxArmor) {
    m_armorBar.setMaxValue(maxArmor);
}

void HealthBar::setArmor(float armor) {
    m_armorBar.setValue(armor);
}

void HealthBar::setPosition(const sf::Vector2f& pos) {
    m_healthBar.setPosition(pos);
    sf::Vector2f armorPos = pos;
    armorPos.y += m_healthBar.getBorder().getSize().y + 5.f;
    m_armorBar.setPosition(armorPos);
}

void HealthBar::draw(sf::RenderWindow& window) const {
    m_healthBar.draw(window);

    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("ARIAL.TTF")) {
        throw std::runtime_error("Failed to load font!");
    }
    text.setFont(font);
    text.setString(
        std::to_string(static_cast<int>(m_healthBar.getValue())) + " / " +
        std::to_string(static_cast<int>(m_healthBar.getMaxValue()))
    );
    text.setCharacterSize(5);
    text.setFillColor(sf::Color::Black);
    text.setPosition(m_healthBar.getBorder().getPosition().x - 10.f,
        m_healthBar.getBorder().getPosition().y - 3.f);
    window.draw(text);

    m_armorBar.draw(window);

    text.setString(
        std::to_string(static_cast<int>(m_armorBar.getValue())) + " / " +
        std::to_string(static_cast<int>(m_armorBar.getMaxValue()))
    );
    text.setPosition(m_armorBar.getBorder().getPosition().x - 10.f,
        m_armorBar.getBorder().getPosition().y - 3.f);
    window.draw(text);
}
