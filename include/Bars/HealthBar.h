#pragma once
#include <SFML/Graphics.hpp>
#include "Bars/Bar.h"

class HealthBar : public  Bar{
public:
    HealthBar(float width, float height, float maxHealth);
	void updateColor() override;
};
