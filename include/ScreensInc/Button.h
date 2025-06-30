#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "CommandInc/Command.h"
#include "Constants.h"

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text = "");

    std::function<void()> m_callback;
    void setCommand(std::unique_ptr<Command> command);
    void setTexture(const Constants::TextureID textureID);
    void updateHover(const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void setText(const std::string& text);
    void centerText();
    sf::Color makeBrighter(const sf::Color& color, float factor);
    void centerText(const sf::Vector2f& position, const sf::Vector2f& size);
private:
    sf::RectangleShape m_shape;

    sf::Text m_text;
    std::unique_ptr<Command> m_command;
    bool m_isHovered = false;


};
