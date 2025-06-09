#include "ScreensInc/Button.h"
#include <iostream>
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text)
{
    m_shape.setSize(size);
    m_shape.setPosition(position);
	std::cout << "Button position: " << position.x << ", " << position.y << std::endl;
    m_shape.setFillColor(m_idleColor);

    m_text.setString(text);
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Black);
}

void Button::setFont(const sf::Font& font) {
    m_text.setFont(font);
    sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(bounds.width / 2, bounds.height / 2);
    m_text.setPosition(
        m_shape.getPosition().x + m_shape.getSize().x / 2,
        m_shape.getPosition().y + m_shape.getSize().y / 2
    );
}

void Button::setCallback(std::function<void()> callback) {
    m_callback = callback;
}

void Button::setTextSize(unsigned int size) {
    m_text.setCharacterSize(size);
}

void Button::setIdleColor(const sf::Color& color) {
    m_idleColor = color;
    m_shape.setFillColor(color);
}

void Button::setHoverColor(const sf::Color& color) {
    m_hoverColor = color;
}

void Button::updateHover(const sf::RenderWindow& window) {
    if (m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
        m_shape.setFillColor(m_hoverColor);
    }
	
    else {
        m_shape.setFillColor(m_idleColor);
    }
}

void Button::render(sf::RenderWindow& window) {
    window.draw(m_shape);
    window.draw(m_text);
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::FloatRect bounds = m_shape.getGlobalBounds();
        if (bounds.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
            if (m_callback)
                m_callback(); // Invoke the function assigned to the button
        }
    }
}
