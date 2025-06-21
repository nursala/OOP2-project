#pragma once

#include "GameObject/Gift.h"



class ExtraArmorGift : public Gift {
public:
	ExtraArmorGift(World& world, sf::Vector2f position);
	//void apply(Player& player) override;
};