#include "GameObject/SpeedUpGift.h"
#include "ResourseInc/TextureManager.h"
#include "GameObject/Player.h"
#include <iostream>

SpeedUpGift::SpeedUpGift(World& world, sf::Vector2f position)
	:Gift(world, TextureManager::instance().get(TextureID::SPEEDUP), { 20, 20 }, { 1, 1 })
{
	m_type = GiftType::SPEEDUP; // Set the type of the gift
	//m_visable = true; // Make sure the gift is visible
}
