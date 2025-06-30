#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Constants.h"

class Statusbar {
public:
    Statusbar();
    void update();
    void render(sf::RenderWindow& window);
private:
    void setNumOfEnemeies();
    void initCoins();
    void initializeText(sf::Text& text, float posX) const;
    void initEnemies();
	void initLevel();
	void initializeTexture(sf::RectangleShape& shape, Constants::TextureID texture, float posX);
    void setText(const std::string text, int index);

    std::vector <sf::Text> m_text;
    std::vector <sf::RectangleShape> m_shape;
};
