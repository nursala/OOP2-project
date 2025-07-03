#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"
#include "AnimationInc/Animation.h"

class LoadGame : public Screen {
public:
	LoadGame();
	virtual ~LoadGame() = default;
	void init() override;
	void update(sf::RenderWindow& window, float dt) override;
	Constants::ScreenID getScreenID() const override;
	void render(sf::RenderWindow& window) override;
private:
	float m_timer;
	std::unique_ptr<Animation> m_animation; // Animation for the character
	sf::Sprite m_sprite; // Sprite for the character
};