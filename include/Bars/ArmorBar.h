#pragma once

#include <SFML/Graphics.hpp>
#include "Bars/Bar.h"

//======================================================
// ArmorBar: visual bar showing player's current armor value.
// Inherits from the abstract base class Bar.
//======================================================
class ArmorBar : public Bar {
public:
    ArmorBar(const float width, const float height, const float maxArmor);

    // Updates the color of the armor bar based on the current value.
    void updateColor() override;
};
