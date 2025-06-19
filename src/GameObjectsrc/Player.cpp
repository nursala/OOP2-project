#include "GameObject/Player.h"
#include <SFML/Window/Keyboard.hpp>
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/KeyboardMoveStrategy.h"
#include "StatesInc/IdleStatePlayer.h"
#include "StatesInc/WalkingStatePlayer.h"
#include <iostream>

Player::Player(World& world)
    : Character(world, TextureManager::instance().get(TextureID::Player), { 150, 150 }, { 5, 5 }, 0.4)
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
