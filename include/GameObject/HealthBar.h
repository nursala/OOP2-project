#pragma once
#include <SFML/Graphics.hpp>

class HealthBar {
public:
    HealthBar(float width = 50.f, float height = 5.f);

    // Set the maximum and current health
    void setMaxHealth(float maxHealth);
    void setHealth(float health);

    // Set the position of the health bar
    void setPosition(const sf::Vector2f& pos);

    // Draw the health bar
    void draw(sf::RenderWindow& window) const;

private:
    void updateBar();

    float m_maxHealth;
    float m_currentHealth;
    sf::RectangleShape m_border;
    sf::RectangleShape m_inner;
};
