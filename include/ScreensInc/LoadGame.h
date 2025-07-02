#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class LoadGame : public Screen {
public:
	LoadGame();
	virtual ~LoadGame() = default;
	void init() override;
	Constants::ScreenID getScreenID() const override;
private:
};