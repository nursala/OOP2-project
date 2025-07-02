#include "ScreensInc/SplashScreen.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include "ScreensInc/HomeScreen.h"
#include "CommandInc/PushScreenCommand.h"
#include "Controller.h"




SplashScreen::SplashScreen() {
    //setBackGroundTexture(Constants::TextureID::GAMEOVER);
    setSize();
    m_backGround.setFillColor(sf::Color::Black);

    if (!m_soundBuffer.loadFromFile("ElevenLabs_Text_to_Speech_audio.ogg")) {
        std::cerr << "Failed to load sound\n";
    }
    m_sound.setBuffer(m_soundBuffer);
    m_sound.play();
}

SplashScreen::~SplashScreen()
{
    m_sound.stop();
}

void SplashScreen::init()
{
    m_generalButtons.clear();

    m_generalButtons.emplace_back(
        Constants::ButtonID::Play,
        "Skip",
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.8f, Constants::WINDOW_HEIGHT * 0.9f),
        sf::Vector2f(Constants::WINDOW_WIDTH * 0.2f, Constants::WINDOW_HEIGHT * 0.1f),
        std::make_unique<PushScreenCommand<HomeScreen>>()
    );
    setButtons(m_generalButtons);

    m_script = {
        {"The city… is gone.", 1.f},
        {"No lights. No power. Just shadows.", 8.f},
        {"The streets… don’t speak anymore.", 15.f},
        {"Only the dead… make noise now.", 20.f},
        {"You…", 32.f},
        {"You are alone in the dark.", 33.f},
        {"Every move… might be your last.", 44.f},
        {"They're watching. Waiting.", 51.f},
        {"Your flashlight… is your only friend. Until it isn’t.", 62.f},
        {"Pick your weapon…  Hold it tight…", 72.f},
        {"Don’t trust the light.", 75.f},
        {"Don’t trust anyone.", 77.f},
        {"This war…", 86.f},
        {"isn’t on the surface.", 87.5f},
        {"This is not a mission —", 91.f},
        {"This… is survival.", 95.f}
    };
}

Constants::ScreenID SplashScreen::getScreenID() const {
    return Constants::ScreenID::SplashScreen;
}

void SplashScreen::render(sf::RenderWindow& window) {
    Screen::render(window);

    float currentTime = m_sound.getPlayingOffset().asSeconds();
    float y = Constants::WINDOW_HEIGHT * 0.1f;

    for (const auto& line : m_script) {
        if (currentTime >= line.timeInSeconds) {
            float elapsed = currentTime - line.timeInSeconds;

            size_t charsToShow = static_cast<size_t>(elapsed / line.charDelay);
            charsToShow = std::min(charsToShow, line.text.size());

            std::string partialText = line.text.substr(0, charsToShow);

            float fadeFactor = std::min(elapsed / line.fadeDuration, 1.f);
            sf::Color color = sf::Color::White;
            color.a = static_cast<sf::Uint8>(255 * fadeFactor);

            sf::Text text;
            text.setFont(Controller::getInstance().getFont());
            text.setString(partialText);
            text.setCharacterSize(24);
            text.setFillColor(color);
            text.setPosition(Constants::WINDOW_WIDTH * 0.1f, y);

            window.draw(text);
            y += 40.f;
        }
    }

    if (currentTime >= m_script.back().timeInSeconds + 3.f) {
        auto it = m_buttons.begin();
        if (it != m_buttons.end()) {
            it->second.execute();
        }
    }
}
