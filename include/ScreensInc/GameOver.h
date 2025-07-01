#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class GameOver : public Screen {
public:
	GameOver();
	virtual ~GameOver() = default;
	void init() override;
	Constants::ScreenID getScreenID() const override;
private:
};