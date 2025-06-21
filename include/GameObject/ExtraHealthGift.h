#pragma once

#include "GameObject/Gift.h"

class ExtraHealthGift : public Gift {
public:
	ExtraHealthGift(World& world, sf::Vector2f position);
	//void apply(Player& player) override;
};