#include "ScreensInc/Button.h"
#include <iostream>
#include "Controller.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text) {
	m_shape.setSize(size);
	m_shape.setPosition(position);
	m_shape.setFillColor(m_idleColor);

	m_text.setFont(Controller::getInstance().getFont()); // ← استخدام الخط المشترك
	m_text.setString(text);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(position.x + 10, position.y + 10);
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

void Button::setText(const std::string& text)
{
	m_text.setString(text);
}
