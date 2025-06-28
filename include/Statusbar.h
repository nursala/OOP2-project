#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "ScreensInc/Button.h"

class Statusbar {
public:
    Statusbar();

    void setTimer(float timeInSeconds);
    void setKills(int kills);
    void setWaves(int waves);

    float getTimer() const;
    int getKills() const;
    int getWaves() const;

    // Render the status bar (implementation depends on your graphics library)
    void render(sf::RenderWindow& window,float elapsedTime, float timeLeft);
    void drawLevels(int levels, sf::RenderWindow& window, sf::Vector2f playerpos);
    void drawLives(int lives, sf::RenderWindow& window, sf::Vector2f playerpos);
    void drawPercentage(float percentage, sf::RenderWindow& window, sf::Vector2f playerpos);
    void drawTimer(sf::Time elapsedTime, float timeLeft, sf::RenderWindow& window, sf::Vector2f playerpos);
    void setFont();

private:
    sf::Font m_font;
    float m_timer;   // Time in seconds
    int m_kills;
    int m_waves;
};