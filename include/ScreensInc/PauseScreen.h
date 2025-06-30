#pragma once

#include "ScreensInc/Screen.h"


class PauseScreen : public Screen {
public:
	PauseScreen();
	virtual Constants::ScreenID getScreenID() const override;
	virtual void init() override;
private:
};