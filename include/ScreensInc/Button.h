#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <string>

enum class ButtonID {
    Play,
    Settings,
    Exit,
    Stop,
    Restart,
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

    void setFont(const sf::Font& font);
    void setCallback(std::function<void()> callback);
    void setTextSize(unsigned int size);
    void setIdleColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);

    void updateHover(const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
    std::function<void()> m_callback;

	sf::Color m_defaultColor = sf::Color::White; // Default color for the button
    sf::Color m_idleColor = sf::Color::Red;
    sf::Color m_hoverColor = sf::Color(200, 200, 200);
    bool m_isHovered = false;
};
