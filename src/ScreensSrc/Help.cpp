#include "ScreensInc/Help.h"
#include "ResourseInc/TextureManager.h"
#include "CommandInc/PopScreenCommand.h"

//-------------------------------------
// Constructor - setup view and background
//-------------------------------------
Help::Help()
{
    setBackGroundTexture(Constants::TextureID::HELP);
    setSize({ Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT_FOR_SCROLL });

    m_view.setSize({ Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT });
    m_view.setCenter(Constants::WINDOW_WIDTH / 2.f, Constants::WINDOW_HEIGHT / 2.f);
}

//-------------------------------------
// Initialize back button and setup commands
//-------------------------------------
void Help::init()
{
    m_generalButtons.clear();

    m_generalButtons.emplace_back(
        Constants::ButtonID::Back,
        "Back",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.9f, Constants::WINDOW_HEIGHT * 0.05f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.1f, Constants::WINDOW_HEIGHT * 0.05f),
        std::make_unique<PopScreenCommand>()
    );

    setButtons(m_generalButtons);
}

//-------------------------------------
// Handle input: mouse scroll or arrow keys
//-------------------------------------
void Help::processEvent(sf::Event& event, sf::RenderWindow& window)
{
    Screen::processEvent(event, window);

    if (event.type == sf::Event::MouseWheelScrolled) {
        m_view.move(0, -event.mouseWheelScroll.delta * m_scrollSpeed);
        clampView();
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up)
            m_view.move(0, -m_scrollSpeed);
        else if (event.key.code == sf::Keyboard::Down)
            m_view.move(0, m_scrollSpeed);
        clampView();
    }
}

//-------------------------------------
// Return screen ID (Help)
//-------------------------------------
Constants::ScreenID Help::getScreenID() const
{
    return Constants::ScreenID::Help;
}

//-------------------------------------
// Render help background and buttons
//-------------------------------------
void Help::render(sf::RenderWindow& window)
{
    window.setView(m_view);
    Screen::render(window);
}

//-------------------------------------
// Clamp the vertical view to avoid scrolling too far
//-------------------------------------
void Help::clampView()
{
    float imageHeight = static_cast<float>(m_backGround.getTexture()->getSize().y);
    float halfViewHeight = m_view.getSize().y / 2.f;

    float topLimit = halfViewHeight;
    float bottomLimit = imageHeight - halfViewHeight;

    sf::Vector2f center = m_view.getCenter();
    if (center.y < topLimit)
        center.y = topLimit;
    if (center.y > bottomLimit)
        center.y = bottomLimit;

    m_view.setCenter(center);
}
