#include "ScreensInc/Screen.h"
#include "ResourseInc/TextureManager.h"

//-------------------------------------
// Screen constructor
Screen::Screen() {
    m_backGround.setPosition(0.0f, 0.0f);
}

//-------------------------------------
// Set background size
void Screen::setSize(const sf::Vector2f& size) {
    m_backGround.setSize(size);
}

//-------------------------------------
// Set background texture
void Screen::setBackGroundTexture(const Constants::TextureID texture) {
    auto tex = TextureManager::instance().get(texture);
    m_backGround.setTexture(tex);
    m_backGround.setTextureRect(sf::IntRect(0, 0, tex->getSize().x, tex->getSize().y));
}

//-------------------------------------
// Render background and all buttons
void Screen::render(sf::RenderWindow& window) {
    window.draw(m_backGround);
    window.setView(window.getDefaultView());
    drawButtons(window);
}

//-------------------------------------
// Update all button hover states
void Screen::update(sf::RenderWindow& window, float dt) {
    (void)dt;
    for (auto& [id, button] : m_buttons) {
        button.updateHover(window);
    }
}

//-------------------------------------
// Handle input events for all buttons
void Screen::processEvent(sf::Event& event, sf::RenderWindow& window) {
    for (auto& [id, button] : m_buttons) {
        button.handleEvent(event, window);
    }
}

//-------------------------------------
// Draw each button
void Screen::drawButtons(sf::RenderWindow& window) 
{
    for (auto& [id, button] : m_buttons) {
        button.render(window);
    }
}

//-------------------------------------
// Return reference to button by ID
Button& Screen::getButton(const Constants::ButtonID id) {
    return m_buttons.at(id);
}
