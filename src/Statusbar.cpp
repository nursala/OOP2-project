#include "Statusbar.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics/Texture.hpp>
#include "ResourseInc/TextureManager.h"
#include "Controller.h"
#include <string>
#include "ResourseInc/TextureManager.h"
#include "Controller.h"
#include "GameSessionData.h"
#include "Constants.h"

//-------------------------------------
// Statusbar Ctor
Statusbar::Statusbar() {
	m_text.resize(Constants::NUM_OF_ITEMS_IN_STATUS_BAR);
	m_shape.resize(Constants::NUM_OF_ITEMS_IN_STATUS_BAR);

	initEnemies();
	initCoins();
	initLevel();
}

//-------------------------------------
// Init Enemies
void Statusbar::initEnemies()
{
	initializeTexture(m_shape[0], Constants::TextureID::KILLS, Constants::MARGIN);
	setNumOfEnemeies();
}

void Statusbar::setNumOfEnemeies() 
{
	int enemies = GameSessionData::instance().getEnemies();
	initializeText(m_text[0], Constants::TILE_IN_STATUS_BAR + Constants::MARGIN);
	std::string text = ": " + std::to_string(enemies);
	setText(text, 0);
}

//-------------------------------------
// Initialize Coins
void Statusbar::initCoins()
{
	initializeTexture(m_shape[1], Constants::TextureID::COINS, Constants::MARGIN + Constants::WINDOW_WIDTH * 0.4);
	std::string moneyText = ": " + std::to_string(GameSessionData::instance().getMoney());
	initializeText(m_text[1], Constants::TILE_IN_STATUS_BAR + Constants::MARGIN + Constants::WINDOW_WIDTH * 0.4);
	setText(moneyText, 1);
}

//-------------------------------------
// Initialize Level
void Statusbar::initLevel()
{
	initializeTexture(m_shape[2], Constants::TextureID::LEVELS, Constants::MARGIN + Constants::WINDOW_WIDTH * 0.7);
	std::string levelText = " :" + Constants::LevelNames[GameSessionData::instance().getLevelID()].first;
	initializeText(m_text[2], Constants::TILE_IN_STATUS_BAR + Constants::MARGIN + Constants::WINDOW_WIDTH * 0.7);
	m_text[2].setFillColor(Constants::LevelNames[GameSessionData::instance().getLevelID()].second);
	setText(levelText, 2);
}

//-------------------------------------
void Statusbar::update()
{
	setNumOfEnemeies();
	std::string moneyText = ": " + std::to_string(GameSessionData::instance().getMoney());
	setText(moneyText, 1);
}

//-------------------------------------
void Statusbar::render(sf::RenderWindow& window) const
{
	for (size_t i = 0; i < m_shape.size(); ++i) 
	{
		window.draw(m_shape[i]);
		window.draw(m_text[i]);
	}
}

//-------------------------------------
// Initialize Text and Texture
void Statusbar::initializeText(sf::Text& text, const float posX) const
{
	text.setFont(Controller::getInstance().getFont());
	text.setCharacterSize(Constants::CHAR_SIZE);
	text.setFillColor(sf::Color::White);
	text.setPosition(posX, Constants::MARGIN);
}

void Statusbar::initializeTexture(sf::RectangleShape& shape, const Constants::TextureID texture, const float posX)
{
	shape.setTexture(TextureManager::instance().get(texture));
	shape.setPosition(posX, Constants::MARGIN);
	shape.setSize(sf::Vector2f(Constants::WINDOW_WIDTH*0.05, Constants::WINDOW_WIDTH * 0.05));
}

//-------------------------------------
// Set Text for Statusbar
void Statusbar::setText(const std::string text, const int index)
{
	m_text[index].setString(text);
}