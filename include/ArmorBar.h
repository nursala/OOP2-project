#pragma once
#include <SFML/Graphics.hpp>
#include "Bar.h"

class ArmorBar : public  Bar {
public:
    ArmorBar(float width, float height, int maxArmor);
	void updateColor() override;
};
