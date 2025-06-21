#include "GameObject/SpyGift.h"
#include "ResourseInc/TextureManager.h"
#include "GameObject/Player.h"
#include <iostream>

SpyGift::SpyGift(World& world, sf::Vector2f position)
	:Gift(world, TextureManager::instance().get(TextureID::SPY), { 20, 20 }, { 1, 1 })
{
	m_type = GiftType::SPY; // Set the type of the gift
	//m_visable = true; // Make sure the gift is visible
}
