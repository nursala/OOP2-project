#include "GameObject/EnemySpDwGift.h"
#include "ResourseInc/TextureManager.h"
#include "GameObject/Player.h"
#include <iostream>

EnemySpDwGift::EnemySpDwGift(World& world, sf::Vector2f position)
	:Gift(world, TextureManager::instance().get(TextureID::ENEMYSPEEDDOWN), { 200, 200 }, { 1, 1 })
{
	m_type = GiftType::ENEMYSPEEDDOWN; // Set the type of the gift
	//m_visable = true; // Make sure the gift is visible
}
