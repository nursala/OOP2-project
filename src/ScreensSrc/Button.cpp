#include "ScreensInc/Button.h"
#include <iostream>
#include "Controller.h"
#include "Constants.h"
#include "ResourseInc/BaseResourceManager.h"

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text)
{
	m_shape.setSize(size);
	m_shape.setPosition(position);
	m_shape.setTexture(TextureManager::instance().get(Constants::TextureID::BUTTON));

	m_text.setFont(Controller::getInstance().getFont());
	m_text.setString(text);
	m_text.setCharacterSize(Constants::CHAR_SIZE);
	m_text.setFillColor(sf::Color::Black);

	centerText();
}

void Button::setCommand(std::unique_ptr<Command> command)
{
	m_command = std::move(command);
}

void Button::setTexture(const Constants::TextureID texture) {
	m_shape.setTexture(TextureManager::instance().get(texture));
	m_shape.setTextureRect(sf::IntRect(0, 0, TextureManager::instance().get(texture)->getSize().x,
							TextureManager::instance().get(texture)->getSize().x));
}

void Button::updateHover(const sf::RenderWindow& window) {
	if (m_shape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
		m_shape.setFillColor(Constants::HOVERD_COLOR);
	}

	else {
		m_shape.setFillColor(Constants::DEFAUL_BUTTON_COLOR);
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

void Button::setText(const std::string& text)
{
	m_text.setString(text);
	centerText();
}

void Button::centerText() {
	sf::FloatRect textBounds = m_text.getLocalBounds();

	m_text.setOrigin(textBounds.left + textBounds.width / 2.0f,
		textBounds.top + textBounds.height / 2.0f);

	sf::Vector2f shapePos = m_shape.getPosition();
	sf::Vector2f shapeSize = m_shape.getSize();

	m_text.setPosition(shapePos.x + shapeSize.x / 2.0f,
		shapePos.y + shapeSize.y / 2.0f);
}
