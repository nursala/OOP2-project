#include "Statusbar.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics/Texture.hpp>
#include "ResourseInc/TextureManager.h"
#include "Controller.h"
#include <string>

Statusbar::Statusbar() {
	m_level = "Easy";
}

void Statusbar::setKills(int kills) { m_kills = kills;}
int Statusbar::getKills() const { return m_kills; }
void Statusbar::setCoins(int coins) { m_coins = coins;}
int Statusbar::getCoins() const { return m_coins; }

void Statusbar::setLevel(std::string level) { m_level = level;}
std::string Statusbar::getLevel() const { return m_level; }

void Statusbar::render(sf::RenderWindow& window) {
	auto viewSize = window.getView().getSize();
    auto pos = window.getView().getCenter();

    float startX = pos.x - viewSize.x / 2;
    float startY = pos.y - viewSize.y / 2 + 10.f;

    drawIconWithText(window, TextureManager::instance().get(Constants::TextureID::KILLS), { startX + 50 , startY }, std::to_string(m_kills));
    drawIconWithText(window, TextureManager::instance().get(Constants::TextureID::COINS), {startX + 350,  startY }, std::to_string(m_coins));
	auto levelColor = m_level == "Easy" ? sf::Color::Green : (m_level == "Medium" ? sf::Color::Yellow : sf::Color::Red);
    drawIconWithText(window, TextureManager::instance().get(Constants::TextureID::LEVELS), { startX + 650,  startY }, m_level, levelColor);
}

void Statusbar::drawIconWithText(sf::RenderWindow& window,const sf::Texture* texture,const sf::Vector2f& pos,std::string value, sf::Color color)
{
    if (!texture) return; // Ensure texture is valid
	sf::Sprite icon;
	icon.setTexture(*texture);
	icon.setPosition(pos);
	icon.setScale(0.4f, 0.4f); // Adjust scale as needed
	// Draw the icon and text
	window.draw(icon);
    sf::Text text;
    text.setFont(Controller::getInstance().getFont());
    text.setCharacterSize(30);
    text.setFillColor(color);
    text.setString(": " + value);
    text.setPosition(pos.x + icon.getGlobalBounds().height + 2, pos.y);
    window.draw(text);
}
    
