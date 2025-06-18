//#include "WeponInc/Gun.h"
//#include "GameObject/Bullet.h"
//#include "WorldInc/World.h"
//
//Gun::Gun() : Weapon()
//{
//	m_bulletSpeed = 500.f;
//	m_cooldown = 0.5f;
//	m_damage = 10.f;   
//}
//
//void Gun::fire(World& world, const sf::Vector2f& position, const sf::Vector2f& direction)
//{
//	if (!canFire())
//		return;
//	Bullet* bullet = new Bullet(world, position, direction, m_bulletSpeed);
//	b2Body* body = bullet->getBody();
//	body->SetUserData(bullet); 
//	//world.getWorld().CreateBody(body);
//	m_currentCooldown = m_cooldown;
//}