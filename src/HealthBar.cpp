#include "HealthBar.h"

HealthBar::HealthBar(float width, float height, int maxHealth)
    : m_maxHealth(maxHealth), m_currentHealth(maxHealth)
{
    m_border.setSize({ width, height });
    m_border.setFillColor(sf::Color(50, 50, 50, 200));
    m_border.setOutlineColor(sf::Color::Black);
    m_border.setOutlineThickness(1.f);
    m_border.setOrigin(width / 2, height / 2);

    m_inner.setSize({ width, height });
    m_inner.setFillColor(sf::Color::Green);
    m_inner.setOrigin(width / 2, height / 2);
}


void HealthBar::setMaxHealth(float maxHealth) {
    m_maxHealth = maxHealth;
    updateBar();
}

void HealthBar::setHealth(float health) {
    m_currentHealth = std::max(0.f, std::min(health, m_maxHealth));
    updateBar();
}

void HealthBar::setPosition(const sf::Vector2f& pos) {
    m_border.setPosition(pos);
    m_inner.setPosition(pos);
}

void HealthBar::draw(sf::RenderWindow& window) const {
    sf::Text text;
    sf::Font font;
    if (!font.loadFromFile("ARIAL.TTF")) {
        throw std::runtime_error("Failed to load font!");
    }
    text.setFont(font);

    // Draw the health bar inner rectangle
    window.draw(m_inner);
    text.setString(std::to_string(static_cast<int>(m_currentHealth)) + " / " + std::to_string(static_cast<int>(m_maxHealth)));
    text.setCharacterSize(5);
    text.setFillColor(sf::Color::Black);
    text.setPosition(m_border.getPosition().x - 10.f, m_border.getPosition().y - 3.f);


    window.draw(m_inner);
    window.draw(m_border);
    window.draw(text);
}

void HealthBar::updateBar() {
    float ratio = (m_maxHealth > 0) ? (m_currentHealth / m_maxHealth) : 0.f;
    float width = m_border.getSize().x;
    m_inner.setSize({ width * ratio, m_border.getSize().y });

    // Color changes: green (healthy), yellow (mid), red (low)
    if (ratio > 0.6f)
        m_inner.setFillColor(sf::Color::Green);
    else if (ratio > 0.3f)
        m_inner.setFillColor(sf::Color::Yellow);
    else
        m_inner.setFillColor(sf::Color::Red);
}