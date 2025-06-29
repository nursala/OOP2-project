#include "ScreensInc/Help.h"
#include "ResourseInc/TextureManager.h"
#include "CommandInc/PopScreenCommand.h"

Help::Help()
{
	setBackGroundTexture(Constants::TextureID::HELP);
	setSize({Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT_FOR_SCROLL});
	m_view.setSize({ 1280.0, 720.0f });
	m_view.setCenter(1280.0f / 2.0f, 720.0f / 2.0f);
}

void Help::init()
{
	m_generalButtons.clear();
	m_generalButtons.emplace_back(
		Constants::ButtonID::Back,
		"Back",
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.9f, Constants::WINDOW_HEIGHT * 0.05f),
		sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
		std::make_unique<PopScreenCommand>()
	);
	setButtons(m_generalButtons);
}

void Help::processEvent(sf::Event& event, sf::RenderWindow& window)
{
	Screen::processEvent(event, window);

	if (event.type == sf::Event::MouseWheelScrolled) {
		m_view.move(0, -event.mouseWheelScroll.delta * m_scrollSpeed);
		clampView();
	}
	else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up)
			m_view.move(0, -m_scrollSpeed);
		else if (event.key.code == sf::Keyboard::Down)
			m_view.move(0, m_scrollSpeed);
		clampView();
	}
}

Constants::ScreenID Help::getScreenID() const
{
	return Constants::ScreenID::Help;
}

void Help::render(sf::RenderWindow& window) {
	window.setView(m_view);
	Screen::render(window);
	//window.setView(window.getDefaultView()); 
}

void Help::clampView() {
	float imageHeight = static_cast<float>(m_backGround.getTexture()->getSize().y);
	float halfViewHeight = m_view.getSize().y / 2.0f;

	float topLimit = halfViewHeight;
	float bottomLimit = imageHeight - halfViewHeight;

	sf::Vector2f center = m_view.getCenter();
	if (center.y < topLimit)
		center.y = topLimit;
	if (center.y > bottomLimit)
		center.y = bottomLimit;

	m_view.setCenter(center);
}
