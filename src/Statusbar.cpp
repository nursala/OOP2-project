#include "Statusbar.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <SFML/Graphics/Texture.hpp>
#include "ResourseInc/TextureManager.h"
#include <string>

Statusbar::Statusbar() {
    setFont();
}

void Statusbar::setFont() {
    if (!m_font.loadFromFile("ARIAL.TTF")) {
        std::cerr << "Failed to load font!\n";
    }
}


void Statusbar::setKills(int kills) { m_kills = kills;}
int Statusbar::getKills() const { return m_kills; }
void Statusbar::setCoins(int coins) { m_coins = coins;}
int Statusbar::getCoins() const { return m_coins; }
void Statusbar::setLevel(int level) { m_level = level;}
int Statusbar::getLevel() const { return m_level; }
void Statusbar::setTimer(float seconds) { m_timer = seconds;}

void Statusbar::render(sf::RenderWindow& window, const sf::Vector2f& playerPos, float deltaTime) {
    float startX = playerPos.x;
    float y = playerPos.y + 20.f;

    // Decrease the timer
    if (m_timer > 0.f)
        m_timer -= deltaTime;
    if (m_timer < 0.f)
        m_timer = 0.f;

    drawIconWithText(window, TextureManager::instance().get(TextureID::KILLS), { startX + 50 ,y },std::to_string(m_kills));
    drawIconWithText(window, TextureManager::instance().get(TextureID::COINS), {startX + 350, y},std::to_string(m_coins));
    drawIconWithText(window, TextureManager::instance().get(TextureID::TIMER), { startX + 650, y },std::to_string(m_timer));
    drawIconWithText(window, TextureManager::instance().get(TextureID::LEVELS), { startX + 950, y },std::to_string(m_level));
}

void Statusbar::drawIconWithText(sf::RenderWindow& window,const sf::Texture* texture,const sf::Vector2f& pos,std::string value)
{
    if (!texture) return; // Ensure texture is valid
	sf::Sprite icon;
	icon.setTexture(*texture);
	icon.setPosition(pos);
	icon.setScale(0.5f, 0.5f); // Adjust scale as needed
	// Draw the icon and text
	window.draw(icon);
    sf::Text text;
    text.setFont(m_font);
    text.setCharacterSize(36);
    text.setFillColor(sf::Color::White);
    text.setString(": " + value);
    text.setPosition(pos.x + icon.getGlobalBounds().height + 2, pos.y);
    window.draw(text);
}
    
