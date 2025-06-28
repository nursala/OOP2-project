#include "ScreensInc/Screen.h"
#include "ResourseInc/TextureManager.h"

Screen::Screen()
{
	m_backGround.setPosition(0.0f, 0.0f);

}

void Screen::setSize(const sf::Vector2f& size)
{
	m_backGround.setSize(size);
}

void Screen::setButtons()
{
	for (auto& info : m_buttonInfos)
	{
		auto& btn = m_buttons.emplace(
			info.id,
			Button(info.size, info.position, info.label)
		).first->second;

		btn.setCommand(std::move(info.command));
	}
}

void Screen::setBackGroundTexture(const Constants::TextureID texture)
{
	auto tex = TextureManager::instance().get(texture);
	m_backGround.setTexture(tex);
	m_backGround.setTextureRect(sf::IntRect(0, 0, tex->getSize().x, tex->getSize().y));
}

void Screen::render(sf::RenderWindow& window)
{
	window.draw(m_backGround);
	window.setView(window.getDefaultView());
	drawButtons(window);
}

void Screen::update(sf::RenderWindow& window, float dt)
{
	(void)dt; // Placeholder for delta time, if needed in future
	for (auto& [id, button] : m_buttons)
	{
		button.updateHover(window);
	}
}

void Screen::processEvent(sf::Event& event, sf::RenderWindow& window)
{
	for (auto& [id, button] : m_buttons)
	{
		button.handleEvent(event, window);
	}
}

void Screen::drawButtons(sf::RenderWindow& window)
{
	for (auto& [id, button] : m_buttons)
	{
		button.render(window);
	}
}