#pragma once
#include <SFML/Graphics.hpp>
#include "Bar.h"

class HealthBar {
public:
    HealthBar(float width, float height, int maxHealth, int maxArmor);
    void setMaxHealth(float maxHealth);
    void setHealth(float health);
    void setMaxArmor(float maxArmor);
    void setArmor(float armor);
    void setPosition(const sf::Vector2f& pos);
    void draw(sf::RenderWindow& window) const;
private:
    Bar m_healthBar;
    Bar m_armorBar;
};
