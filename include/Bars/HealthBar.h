#pragma once

#include <SFML/Graphics.hpp>
#include "Bars/Bar.h"

//======================================================
// HealthBar: visual bar showing player's current health.
// Inherits from the abstract base class Bar.
//======================================================
class HealthBar : public Bar {
public:
    HealthBar(float width, float height, float maxHealth);

    // Updates the color of the health bar based on the current value.
    void updateColor() override;
};
