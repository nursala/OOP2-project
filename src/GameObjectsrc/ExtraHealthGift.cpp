#include "GameObject/ExtraHealthGift.h"
#include "GameObject/Gift.h"
#include "ResourseInc/TextureManager.h"
#include "GameObject/Player.h"
#include <iostream>

ExtraHealthGift::ExtraHealthGift(World& world,sf::Vector2f position)
	:Gift(world, TextureManager::instance().get(TextureID::HEALTH),position, { 1, 1 })
{
	m_type = GiftType::HEALTH; // Set the type of the gift
	//m_visable = true; // Make sure the gift is visible
}
