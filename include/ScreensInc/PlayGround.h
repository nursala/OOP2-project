#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"
#include "WorldInc/World.h"
#include <Statusbar.h>
#include <SFML/Graphics/Sprite.hpp>

class PlayGround : public Screen {
public:
    PlayGround();
    virtual ~PlayGround() = default;
    virtual void update(sf::RenderWindow& window, float dt);
    void render(sf::RenderWindow& window) override;
    Constants::ScreenID getScreenID() const override;

protected:
    void setSpecialButtons() override;
    void init() override;

private:
    sf::View m_view;
    World m_world;
    Statusbar m_statusBar;

    sf::Sprite m_winSprite;            // To hold the GAMEWIN texture
    bool m_showWinScreen = false;      // To track when to show it
    bool m_winSoundPlayed = false;     // To ensure sound plays once
};
