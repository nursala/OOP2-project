#pragma once
#include <SFML/Graphics.hpp>

class Animation {
public:
    Animation(const sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    void update(int row, float deltaTime);
    void setAll(const sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float deltaTime);
    const sf::IntRect& getUvRect() const;
private:
    sf::Vector2u m_imageCount;    
    sf::Vector2u m_currentImage;   
    float m_totalTime;            
    float m_switchTime;            
    int m_totalImages;            
    int m_displayed;         
    sf::IntRect m_uvRect;         
};
