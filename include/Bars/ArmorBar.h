#pragma once
#include <SFML/Graphics.hpp>
#include "Bars/Bar.h"

class ArmorBar : public  Bar {
public:
    ArmorBar(float width, float height, float maxArmor);
	void updateColor() override;
};
