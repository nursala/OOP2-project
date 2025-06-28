#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class HomeScreen : public Screen {
public:
	HomeScreen();
	virtual ~HomeScreen() = default;
	void init() override;
	Constants::ScreenID getScreenID() const override;
private:
};