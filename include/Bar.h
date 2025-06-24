#pragma once
#include <SFML/Graphics.hpp>

class Bar {
public:
    Bar(float width, float height, sf::Color color,float maxValue);
	virtual ~Bar() = default;
    void setMaxValue(float maxValue);
    void setValue(float value);
    void setPosition(const sf::Vector2f& pos);
    void draw(sf::RenderWindow& window) const;
    float getValue() const { return m_currentValue; }
    float getMaxValue() const { return m_maxValue; }
    const sf::RectangleShape& getBorder() const { return m_border; }
    virtual void updateColor() = 0;
protected:
    float m_maxValue;
    float m_currentValue;
    sf::RectangleShape m_border;
    sf::RectangleShape m_inner;

private:
    void updateBar();
    void setFont();
	sf::Font m_font;
};
