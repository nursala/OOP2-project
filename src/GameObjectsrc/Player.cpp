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
