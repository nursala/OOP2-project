#pragma once
#include "ScreensInc/Screen.h"
#include "ScreensInc/Button.h"
#include "ResourseInc/TextureManager.h"

class GameWin : public Screen {
public:
	GameWin();
	virtual ~GameWin() = default;
	void init() override;
	Constants::ScreenID getScreenID() const override;
private:
};