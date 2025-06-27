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
    void setLevel(int level);
    int getLevel() const;
    void setTier(int tier);
    void setTimer(float seconds);

    void render(sf::RenderWindow& window, const sf::Vector2f& playerPos, float deltaTime);

    void drawIconWithText(sf::RenderWindow& window, const sf::Texture* texture, const sf::Vector2f& pos, std::string value);

private:
    sf::Font m_font;

    int m_kills = 0;
    int m_coins = 0;
    int m_level = 1;
    float m_timer = 0.f;  // Remaining time in seconds

    std::unordered_map<std::string, sf::Texture> m_textures;
    std::unordered_map<std::string, sf::Sprite> m_icons;

    void setFont();
    void loadIcons();

    void drawIconWithText(sf::RenderWindow& window,
        float x, float y);
};
