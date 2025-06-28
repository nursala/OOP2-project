#include "RenderLayers.h"

RenderLayers::RenderLayers()
	: m_lightingArea(candle::LightingArea::FOG, { 0.f, 0.f }, { 1280.f, 720.f })
{
	m_lightingArea.setAreaColor(sf::Color::Black);
	m_lightingArea.setAreaOpacity(0.85f);
	m_background.create(1280, 720);
	m_foreground.create(1280, 720);
	m_background.setSmooth(true);
	m_foreground.setSmooth(true);
}

void RenderLayers::setView(const sf::View& view)
{
	m_view = view;
	m_background.setView(view);
	m_foreground.setView(view);
	m_lightingArea.setPosition(view.getCenter() - view.getSize()/2.f);
}



void RenderLayers::clear()
{
	m_background.clear(sf::Color::Transparent);
	m_lightingArea.clear();
	m_foreground.clear(sf::Color::Transparent);
}

void RenderLayers::drawBackground(const sf::Drawable& drawable)
{
	m_background.draw(drawable, sf::BlendAdd);
}

void RenderLayers::drawForeground(const sf::Drawable& drawable)
{
	m_foreground.draw(drawable , sf::BlendAdd);
}

void RenderLayers::drawLight(candle::LightSource& light)
{
	auto& oldScale = light.getScale();
	auto oldIntensity = light.getIntensity();
	light.setScale({ 0.97f, 0.97f });
	light.setIntensity(1.f); // Set a default intensity for the light
	m_lightingArea.draw(light);
	light.setScale(oldScale);
	light.setIntensity(oldIntensity); // Restore the original intensity
}

void RenderLayers::display()
{
	m_background.display();
	m_foreground.display();
	m_lightingArea.display();
}

void RenderLayers::renderFinal(sf::RenderTarget& target) const
{
	sf::Sprite bg(m_background.getTexture());
	sf::Sprite fg(m_foreground.getTexture());

	sf::Vector2f topLeft = m_view.getCenter() - m_view.getSize() / 2.f;
	sf::Vector2f scale(
		m_view.getSize().x / (m_background.getSize().x),
		m_view.getSize().y / (m_background.getSize().y)
	);

	bg.setPosition(topLeft);
	fg.setPosition(topLeft);
	bg.setScale(scale);
	fg.setScale(scale);

	target.draw(bg);
	target.draw(m_lightingArea);
	target.draw(fg);
}

