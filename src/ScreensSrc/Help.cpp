#include "ScreensInc/Help.h"
#include "ResourseInc/TextureManager.h"
#include "CommandInc/PopScreenCommand.h"

Help::Help() : Screen()
{
	 setBackGroundTexture(TextureID::HELP);
     m_view.setSize({ 1280.0, 720.0f });

     m_view.setCenter(1280.0f / 2.0f, 720.0f / 2.0f);
}

void Help::init()
{
	auto& back = m_buttons.emplace(ButtonID::Back, Button({ 120, 40 }, { 100, 100 }, "Back")).first->second;
	back.setCommand(std::make_unique<PopScreenCommand>());
}

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

ScreenID Help::getScreenID() const
{
	return ScreenID::Help;
}


void Help::render(sf::RenderWindow& window) {
    window.setView(m_view);
    Screen::render(window);


    //window.setView(window.getDefaultView()); 
}

void Help::clampView() {
    float imageHeight = static_cast<float>(m_backGround.getTexture()->getSize().y);
    float halfViewHeight = m_view.getSize().y / 2.0f;

    float topLimit = halfViewHeight;
    float bottomLimit = imageHeight - halfViewHeight;

    sf::Vector2f center = m_view.getCenter();
    if (center.y < topLimit)
        center.y = topLimit;
    if (center.y > bottomLimit)
        center.y = bottomLimit;

    m_view.setCenter(center);
}
