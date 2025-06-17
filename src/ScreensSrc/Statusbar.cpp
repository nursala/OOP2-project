#include "ScreensInc/Statusbar.h"
#include <iostream> // For demonstration, replace with your rendering system
#include <SFML/Graphics/RenderWindow.hpp>
#include "ScreensInc/Button.h"

Statusbar::Statusbar()
    : m_timer(0.0f), m_kills(0), m_waves(0) {
	setFont();
}

void Statusbar::setTimer(float timeInSeconds) {
    m_timer = timeInSeconds;
}

void Statusbar::setKills(int killsCount) {
    m_kills = killsCount;
}

void Statusbar::setWaves(int wavesCount) {
    m_waves = wavesCount;
}

float Statusbar::getTimer() const {
    return m_timer;
}

int Statusbar::getKills() const {
    return m_kills;
}

int Statusbar::getWaves() const {
    return m_waves;
}

void Statusbar::render(sf::RenderWindow& window, float elapsedTime, float timeLeft, sf::Vector2f playerpos){

	float x = playerpos.x;
	float y = playerpos.y;
    sf::Text text;
    text.setFont(m_font);
    float curTimeLeft = timeLeft - elapsedTime + 1;
    text.setString("Left: " + std::to_string((int)curTimeLeft));
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::White);
	text.setPosition(x, y);
    window.draw(text);
}

void Statusbar::drawLevels(int levels, sf::RenderWindow& window, sf::Vector2f playerpos)
{
	float x = playerpos.x + 100;
	float y = playerpos.y + 5;
	sf::Text text;
	text.setFont(m_font);
	text.setString("Level: " + std::to_string(levels));
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
	text.setPosition(x, y);
	window.draw(text);
}

void Statusbar::drawLives(int lives, sf::RenderWindow& window, sf::Vector2f playerpos)
{
	float x = playerpos.x;
	float y = playerpos.y;
	sf::Text text;
	text.setFont(m_font);
	text.setString("Lives: " + std::to_string(lives));
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
	text.setPosition(x, y);
	window.draw(text);
}

void Statusbar::drawPercentage(float percentage, sf::RenderWindow& window, sf::Vector2f playerpos)
{
	float x = playerpos.x;
	float y = playerpos.y;
	sf::Text text;
	text.setFont(m_font);
	text.setString("Full: " + std::to_string((int)percentage) + "%");
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
	text.setPosition(x,y);
	window.draw(text);
}

void Statusbar::drawTimer(sf::Time elapsedTime, float timeLeft, sf::RenderWindow& window,sf::Vector2f playerpos)
{
	float x = playerpos.x + 5;
	float y = playerpos.y + 5;
	sf::Text text;
	text.setFont(m_font);
	float curTimeLeft = timeLeft - elapsedTime.asSeconds() + 1;
	text.setString("Left: " + std::to_string((int)curTimeLeft));
	text.setCharacterSize(10);
	text.setFillColor(sf::Color::White);
	text.setPosition(x,y);
	
	window.draw(text);
}

void Statusbar::setFont()
{
    m_font.loadFromFile("ARIAL.TTF");
}
