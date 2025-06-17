#include "ScreensInc/Button.h"
#include <iostream>
Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text)
{
	m_shape.setSize(size);
	m_shape.setPosition(position);
	m_shape.setFillColor(m_idleColor);

	m_text.setString(text);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::Black);
}

void Button::setCommand(std::unique_ptr<Command> command)
{
	m_command = std::move(command);
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
			if (m_command) {
				m_command->execute();
			}
			else {
				std::cerr << "Error: Command not set for this button!" << std::endl;
			}
		}
	}
}
