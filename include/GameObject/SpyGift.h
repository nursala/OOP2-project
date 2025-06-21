#pragma once

#include "GameObject/Gift.h"



class SpyGift : public Gift {
public:
	SpyGift(World& world, sf::Vector2f position);
	//void apply(Player& player) override;
};