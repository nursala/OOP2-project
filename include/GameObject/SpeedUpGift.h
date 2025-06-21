#pragma once

#include "GameObject/Gift.h"



class SpeedUpGift : public Gift {
public:
	SpeedUpGift(World& world, sf::Vector2f position);
	//void apply(Player& player) override;
};