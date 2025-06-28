#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class Statusbar {
public:
    Statusbar();

    void setKills(int kills);
    int getKills() const;
    void setCoins(int coins);
    int getCoins() const;
    void setLevel(std::string level);
    std::string getLevel() const;
    void render(sf::RenderWindow& window);

private:
    void drawIconWithText(sf::RenderWindow& window, const sf::Texture* texture, const sf::Vector2f& pos, std::string value, sf::Color color = sf::Color::White);
    sf::Font m_font;

    int m_kills = 0;
    int m_coins = 0;
    std::string m_level;

    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Sprite> m_icons;

    void setFont();
    void loadIcons();

    void drawIconWithText(sf::RenderWindow& window,
        float x, float y);
};
