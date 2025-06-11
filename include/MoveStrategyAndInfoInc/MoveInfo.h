#pragma once
#include <SFML/Graphics.hpp>

struct MoveInfo {
    int row = 1;
    bool faceRight = true;
	sf::Vector2f direction = { 0.f, 0.f }; 
};