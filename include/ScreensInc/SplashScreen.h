#pragma once

#include "ScreensInc/Screen.h"
#include "ResourseInc/TextureManager.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Clock.hpp>

class SplashScreen : public Screen {
public:
    struct TimedLine {
        std::string text;
        float timeInSeconds;
        float fadeDuration = 1.f; 
        float charDelay = 0.1f;

    };
    SplashScreen();
    ~SplashScreen() = default;

    Constants::ScreenID getScreenID() const override;

    void render(sf::RenderWindow& window)override;


protected:
    void setSpecialButtons() override {};
    void init() override ;

private:
    sf::Sprite m_logo;
    sf::Text m_title;
    sf::Text m_instruction;

    std::vector<sf::Text> m_lines;   // The lines to display
    sf::Clock m_textTimer;           // Controls the timing between lines
    size_t m_currentLine = 0;        // How many lines are currently visible

    sf::Font m_font;
    sf::Clock m_clock;
    bool m_finished = false;
    std::vector<TimedLine> m_script;


    sf::SoundBuffer m_soundBuffer;
    sf::Sound m_sound;
};
