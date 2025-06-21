#include "GameObject/ExtraArmorGift.h"
#include "ResourseInc/TextureManager.h"
#include "GameObject/Player.h"
#include <iostream>

ExtraArmorGift::ExtraArmorGift(World& world,sf::Vector2f position)
	:Gift(world, TextureManager::instance().get(TextureID::ARMOR), position, { 1 , 1 })
{
	m_type = GiftType::ARMOR; // Set the type of the gift
	//m_visable = true; // Make sure the gift is visible
}
