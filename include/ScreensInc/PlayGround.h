#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"
#include "WorldInc/World.h"
#include <Statusbar.h>
//PlayGround.h
class PlayGround : public Screen {
public:
	PlayGround();
	virtual ~PlayGround() = default;
	virtual void update(sf::RenderWindow& window, float dt);
	void render(sf::RenderWindow& window) override;
	Constants::ScreenID getScreenID() const override;
	//virtual void processEvent(sf::Event& event, sf::RenderWindow& window);
protected:
	void init() override;
private:
	sf::View m_view;
	World m_world;
	Statusbar m_statusBar;

};