#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "StatesInc/IdleStatePlayer.h"
#include "StatesInc/WalkingStatePlayer.h"
#include <iostream>
#include "WeponInc/Gun.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"

Player::Player(World& world)
    : Character(world, TextureManager::instance().get(TextureID::Player), { 10, 10 }, { 5, 5 }, 0.4)
{
	std::cout << "Player created" << std::endl;
    m_state = std::make_unique<WalkingStatePlayer>();
    m_moveStrategy = std::make_unique<KeyboardMoveStrategy>();
	m_attackStrategy = std::make_unique<SimpleShootStrategy>();
    if (m_state)
        m_state->enter(*this);

    m_weapon = std::make_unique<Gun>();

    m_visable = true;
   
}

void Player::setLight(std::shared_ptr<VisionLight>& visionLight)
{
    m_visionLight = visionLight;
}

void Player::setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight)
{
    if (m_weapon)
        m_weapon->setLight(weaponLight);
}

void Player::setFacingRight(bool right)
{
    if (m_lastMoveInfo.faceRight != right) {
        m_lastMoveInfo.faceRight = right;

        sf::Vector2f currentScale = m_sprite.getScale();
        m_sprite.setScale(right ? std::abs(currentScale.x) : -std::abs(currentScale.x), currentScale.y);
    }
}

void Player::takeDamage(int damage)
{
    if (m_armor > 0) {
        float armorDamage = std::min(m_armor, static_cast<float>(damage));
        m_armor -= armorDamage;
        damage -= static_cast<int>(armorDamage);
    }
    if (damage > 0) {
        m_health -= damage;
        if (m_health < 0.f) m_health = 0.f;
    }

    //  Update the health bar (use Character's member)
    m_healthBar->setValue(m_health);
    m_armorBar->setValue(m_armor);
}

void Player::addHealth()
{
	m_health += 30; // Increase health by 20
	if (m_health > 100) m_health = 100; // Cap health at 100
	m_healthBar->setValue(m_health);
}

void Player::addArmor()
{
	m_armor += 30; // Increase armor by 10
	if (m_armor > 50) m_armor = 50; // Cap armor at 50
	m_armorBar->setValue(m_armor);
}

void Player::addSpeed()
{
	m_speed += 0.5f; // Increase speed by 0.5
	if (m_speed > 5.f) m_speed = 5.f; // Cap speed at 5
	std::cout << "Player speed increased to: " << m_speed << std::endl;
}

sf::Vector2f Player::getTarget() const
{
	return m_target->getPosition();
}

std::pair<bool, float> Player::EnemyIsVisible()  
{  
   auto WeaponLight = m_weapon->getWeaponLight();  
   if (m_visionLight) {  
       auto closestTarget = WeaponLight->getClosestTarget(this);  
       if (closestTarget) {  
           m_target = closestTarget; 
           sf::Vector2f diff = getPosition() - closestTarget->getPosition();  
           return {true, std::sqrt(diff.x * diff.x + diff.y * diff.y)}; // Fix syntax for returning a pair.  
       }  
   }  
   return {false, 0.0f};
}

