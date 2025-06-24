#pragma once
#include <SFML/Graphics.hpp>
#include "Bar.h"

class ArmorBar : public  Bar {
public:
    ArmorBar(float width, float height, float maxArmor);
	void updateColor() override;
};
