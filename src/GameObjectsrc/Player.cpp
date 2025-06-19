#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "StatesInc/IdleStatePlayer.h"
#include "StatesInc/WalkingStatePlayer.h"
#include <iostream>

Player::Player(World& world)
    : Character(world, TextureManager::instance().get(TextureID::Player), { 100, 100 }, { 5, 5 }, 0.4)
{
    m_state = std::make_unique<IdleStatePlayer>();
    m_moveStrategy = std::make_unique<KeyboardMoveStrategy>();
   
    if (m_state)
        m_state->enter(*this);

    //m_weapon = std::make_unique<Weapon>(world);

    m_visable = true;
}

void Player::setLight(std::shared_ptr<VisionLight>& visionLight)
{
    m_visionLight = visionLight;
}

void Player::setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight)
{
    /*if (m_weapon)
        m_weapon->setLight(weaponLight);*/
}

void Player::setFacingRight(bool right)
{
    if (m_lastMoveInfo.faceRight != right) {
        m_lastMoveInfo.faceRight = right;

        sf::Vector2f currentScale = m_sprite.getScale();
        m_sprite.setScale(right ? std::abs(currentScale.x) : -std::abs(currentScale.x), currentScale.y);
    }
}

void Player::setHealthBar(HealthBar* healthBar)
{
    m_healthBar = healthBar;
    if (m_healthBar) {
        m_healthBar->setHealth(m_health);
        m_healthBar->setArmor(m_armor);
    }

}

void Player::takeDamage(int damage)
{
    if (m_armor > 0) {
        float armorDamage = std::min(m_armor, (float)damage);
        m_armor -= armorDamage;
        damage -= static_cast<int>(armorDamage);
    }
    if (damage > 0) {
        m_health -= damage;
        if (m_health < 0.f) m_health = 0.f;
    }
    // Update the health bar if it's set
    if (m_healthBar) {
        m_healthBar->setHealth(m_health);
        m_healthBar->setArmor(m_armor);
    }
}
