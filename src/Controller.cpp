#include "Controller.h"
#include "ScreensInc/PlayGround.h"
#include "ScreensInc/HomeScreen.h"
#include "ScreensInc/Market.h"

Controller& Controller::getInstance() {
    static Controller instance;
    return instance;
}

// Constructor
Controller::Controller()
    : m_window(sf::VideoMode(1280, 720), "Game Window") 
{
    m_window.setFramerateLimit(60);

	if (!m_font.loadFromFile("myFont.otf")) {
		throw std::runtime_error("Failed to load font");
	}
}

const sf::Font& Controller::getFont() {
	return m_font;
}

// Push a new screen onto the stack
void Controller::pushScreen(std::unique_ptr<Screen> screen) {
    if (screen) {
        screen->setScreenAction([this](ScreenID id) {
            this->setScreen(id);
            });
        m_screens.push(std::move(screen));
    }
}

// Pop the top screen from the stack
void Controller::popScreen() {
    if (!m_screens.empty()) {
        m_screens.pop();
    }
}

void Controller::popToHome()
{
    while (!m_screens.empty()) {
        if (m_screens.top()->getScreenID() == ScreenID::Home)
            break;
        m_screens.pop();
    }
}

// Optional set/remove screen (legacy or switching style)
void Controller::setScreen(ScreenID screen) {
    m_nextScreen = screen;
}

void Controller::removeScreen() {
    popScreen();
}

// Main game loop
void Controller::run() {
    pushScreen(std::make_unique<HomeScreen>());
    while (m_window.isOpen()) {
        if (m_screens.empty()) {
            m_window.close();
            break;
        }

        processEvents();
        update();
        render();
    }
}

void Controller::setPopFlag() {
    m_shouldPop = true;
}

// Handle input
void Controller::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            m_window.close();
        else
            m_screens.top()->processEvent(event, m_window);
    }
}

// Update current screen
void Controller::update() {
    float dt = m_clock.restart().asSeconds();
    m_screens.top()->update(m_window, dt);
	if (m_shouldPop) {
		popScreen();
		m_shouldPop = false;
	}
}

// Render current screen
void Controller::render() {
    m_window.clear();
    m_screens.top()->render(m_window);
    m_window.display();
}
