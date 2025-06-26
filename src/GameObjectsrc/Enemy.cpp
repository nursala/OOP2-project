#include "GameObject/Enemy.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include "MoveStrategyAndInfoInc/IQChaseStrategy.h"
#include "StatesInc/ChasingState.h"
#include "AttackingStrategyInc/SimpleShootStrategy.h"
#include "WorldInc/World.h"
#include <cmath>
#include "WeaponInc/HandGun.h"
#include <limits>

Enemy::Enemy(World& world, const LoadMap& map, const Player& player)
    : Character(world, TextureManager::instance().get(TextureID::Enemy), { 150, 150 }, { 3, 7 }, 0.4f),
    m_playerRef(player)
{
    m_moveStrategy = std::make_unique<IQChaseStrategy>(player, map, rand() % 10 + 1);
    m_state = std::make_unique<ChasingState>();
    if (m_state)
        m_state->enter(*this);

    m_attackStrategy = std::make_unique<SimpleShootStrategy>();
    m_weapon = std::make_unique<HandGun>();
    m_speed = m_originalSpeed = 5.f;  // store original speed
    m_armorBar = nullptr;
}

Enemy::~Enemy() {
    if (m_body)
        m_body->GetWorld()->DestroyBody(m_body);
}

Character* Enemy::getClosestTarget()
{
    if (m_target  && !m_target->isDestroyed()) {
        for (b2Fixture* fixture = m_target->getBody()->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
            if (m_hitFixtures.find(fixture) != m_hitFixtures.end()) {
                return m_target;
            }
        }
    }
    if (m_target) {
        sf::Vector2f targetPos = m_target->getPosition();
        sf::Vector2f selfPos = getPosition(); // أو مصدر الضوء مثلاً

        float dx = targetPos.x - selfPos.x;
        float dy = targetPos.y - selfPos.y;
        float distSq = dx * dx + dy * dy;

        float radius = m_target->getWeapon()->getWeaponLight()->getRange();
        if (distSq <= radius * radius) {
            return m_target;
        }
    }
    if (m_hitFixtures.empty())
    {
		m_target = nullptr; // No targets found
        return nullptr;
    }

  

    Character* closestCharacter = nullptr;
    float minDistSq = std::numeric_limits<float>::max();
    sf::Vector2f lightPos = m_weapon->getWeaponLight()->getPosition();

    for (auto* fixture : m_hitFixtures) {
        b2Body* body = fixture->GetBody();
        auto* character = reinterpret_cast<Character*>(body->GetUserData().pointer);

        if (!character || !character->isVisible()) continue;

       
		auto* enemy = dynamic_cast<Enemy*>(character);
        if (enemy)
        {
            if (this->isSpy() && enemy->isSpy())
                 continue; // Skip spy enemies
			if (!enemy->isSpy() && !this->isSpy())
				continue; // Skip non-spy enemies if this is a spy
        }
        if (auto* P = dynamic_cast<Player*>(character) ; P)
        {
			if (this->isSpy())
				continue; // Skip player if they are a spy
        }
       

        
        sf::Vector2f charPos = character->getPosition();
        float dx = charPos.x - lightPos.x;
        float dy = charPos.y - lightPos.y;
        float distSq = std::sqrt(dx * dx + dy * dy);

        if (distSq < minDistSq) {
            if (closestCharacter && dynamic_cast<Player*>(closestCharacter) && !isSpy())
            {

            }
            else
            {
                minDistSq = distSq;
                closestCharacter = character;
            }
        }
    }
	if (!closestCharacter) {
		m_target = nullptr; // No valid target found
		return nullptr;
	}
	m_target = closestCharacter; // Update target reference
    return closestCharacter;
}



void Enemy::fireBullet(const sf::Vector2f&) {
    // if (m_weapon)
    //     m_weapon->shoot(getPosition(), direction);
}

void Enemy::takeDamage(int damage) {
    damage += 100;
    if (m_health > 0) {
        m_health -= damage;
        if (m_health < 0.f) m_health = 0.f;
    }
    m_healthBar->setValue(m_health);
}

sf::Vector2f Enemy::getTarget() const {
	
	return m_playerRef.getPosition();  // Return player's position as target
}

void Enemy::update(float deltaTime) {
    Character::update(deltaTime);

    if (m_health <= 0.f) {
        setDestroyed(true);
        return;
    }

    // Handle spy timeout
    if (m_isSpy) {
        m_spyTimer -= deltaTime;
        if (m_spyTimer <= 0.f) {
            //m_isSpy = false;
            m_sprite.setColor(sf::Color::White);
        }
        
    }

    // Handle speed reset
    if (m_speedDownTimer > 0.f) {
        m_speedDownTimer -= deltaTime;
        if (m_speedDownTimer <= 0.f) {
            m_speed = m_originalSpeed;  // reset to normal speed
        }
    }
    if (m_isSpy)
        m_weapon->getWeaponLight()->setColor(sf::Color::Blue);
    else
        m_weapon->getWeaponLight()->setColor(sf::Color::Red);
}

void Enemy::speedDown() {
    m_speed -= 0.5f;
    if (m_speed < 1.f) m_speed = 1.f;
}

void Enemy::setSpeedDownTimer(float seconds) {
    speedDown();               // Apply slow
    m_speedDownTimer = seconds;
}

void Enemy::setSpy(bool value) {
    m_isSpy = value;
	m_target = nullptr; // Clear target when becoming a spy
    
}

bool Enemy::isSpy() const {
    return m_isSpy;
}

void Enemy::setSpyTimer(float seconds) {
    m_spyTimer = seconds;
}
