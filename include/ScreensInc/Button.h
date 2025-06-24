#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>
#include "CommandInc/Command.h"

enum class ButtonID {
    Play,
    Settings,
    Exit,
    Stop,
	Back,
	BasicGun,
	Shotgun,
	Sniper,
	Rifle,
};

namespace std {
    template<>
    struct hash<ButtonID> {
        std::size_t operator()(const ButtonID& id) const noexcept {
            return static_cast<std::size_t>(id);
        }
    };
}

class Button {
public:
    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text);

    std::function<void()> m_callback;
    void setCommand(std::unique_ptr<Command> command);
    void updateHover(const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void setText(const std::string& text);
private:
    sf::RectangleShape m_shape;

    sf::Text m_text;
    std::unique_ptr<Command> m_command;
	sf::Color m_defaultColor = sf::Color::White; 
    sf::Color m_idleColor = sf::Color::Red;
    sf::Color m_hoverColor = sf::Color(200, 200, 200);
    bool m_isHovered = false;
};
