#pragma once

#include "GameObject/Gift.h"



class EnemySpDwGift: public Gift {
public:
	EnemySpDwGift(World& world, sf::Vector2f position);
	//void apply(Player& player) override;
};