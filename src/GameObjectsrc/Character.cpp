#include "GameObject/Character.h"
#include "WorldInc/World.h"
#include "VisionLight.h"
#include "StatesInc/AttackingStatePlayer.h"
#include <iostream>


Character::Character(World& world, const sf::Texture* texture, sf::Vector2f position, sf::Vector2u imageCount, float switchTime)
    : Entity(world, texture, position, imageCount, switchTime), m_world(world)
{
	m_visionLight = std::make_unique<VisionLight>(200.f, 60.f); // Default range and beam angle
	m_visionLight->setIntensity(0.7f); // Set default intensity for the weapon light

	m_healthBar = std::make_unique<HealthBar>(50.f, 5.f,100);
}

void Character::update(float deltaTime) {
	this->updateTargets();
	if (m_state) {
		auto newState = m_state->handleInput(*this);
		if (newState) {
			m_state = std::move(newState);
			m_state->enter((*this));
		}
		m_state->update((*this), deltaTime);
	}

    if (m_weapon)
    {
        m_weapon->update(getPosition(),this->getBody()->GetAngle(), deltaTime);
    }

    //if (m_visionLight)
    //{
    //    m_visionLight->update(getPosition(), this->getBody()->GetAngle());
    //}

	m_sprite.setPosition(getPosition());
	m_sprite.setTextureRect(m_animation.getUvRect());

    sf::Vector2f healthBarPos = { getPosition().x , getPosition().y + 30};
    m_healthBar->setPosition(healthBarPos);
	m_healthBar->setValue(m_health);
    if (m_armorBar != nullptr)
    {
        sf::Vector2f armorBarPos = { getPosition().x , getPosition().y + 20 };
        m_armorBar->setPosition(armorBarPos);
        // Update health and armor bars
        m_armorBar->setValue(m_armor);
    }
	if (m_visionLight)
	{
		m_visionLight->update(getPosition(), this->getBody()->GetAngle() / 30.f);
	}
	if (m_weapon->getWeaponLight() || m_visionLight)
	{
		auto& CloseEdges = m_world.getCloseEdges();
		if (m_weapon->getWeaponLight())
			m_weapon->getWeaponLight()->castLight(CloseEdges.begin(), CloseEdges.end());
		if (m_visionLight)
			m_visionLight->castLight(CloseEdges.begin(), CloseEdges.end());
	}



}

void Character::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
    m_healthBar->draw(window);
	if(m_armorBar)
		m_armorBar->draw(window);
}

void Character::render(RenderLayers& renderLayers) {
	renderLayers.drawForeground(m_sprite);
	m_healthBar->draw(renderLayers);
	if (m_armorBar)
		m_armorBar->draw(renderLayers);

	if (m_visionLight)
	{
		renderLayers.drawLight(*m_visionLight);
		renderLayers.drawForeground(*m_visionLight);
	}
	if (m_weapon)
		m_weapon->draw(renderLayers);
	
}
	

const MoveInfo& Character::getLastMoveInfo()
{
	return m_lastMoveInfo;
}

b2BodyType Character::getBodyType() const
{
	return b2_dynamicBody;
}

void Character::move(float dt)
{
	if (m_moveStrategy)
	{
		m_lastMoveInfo = m_moveStrategy->move(*this, dt);
	}
}

Weapon* Character::getWeapon()
{
	return m_weapon.get();
}

void Character::shoot(float dt) {

	if (m_attackStrategy)
	{
		m_attackStrategy->attack(*this, dt);
	}
}

float Character::getShootingRange() const {
	if (m_weapon) {
		return m_weapon->getShootingRange();
	}
	return 0.f;
}

void Character::setShootingRange(float range)
{
	if (m_weapon) {
		m_weapon->setShootingRange(range);
	}
}

void Character::setRotation(float angle)
{
	if (m_body) {
		m_body->SetTransform(b2Vec2(getPosition().x / SCALE, getPosition().y / SCALE), angle * SCALE);
		m_sprite.setRotation(angle);
	}
}

Character* Character::getClosestTarget(const Character* self) 
{
	
	Character* closestCharacter = nullptr;
	float minDistSq = std::numeric_limits<float>::max();
	sf::Vector2f lightPos = m_weapon->getWeaponLight()->getPosition();

	bool lookingForEnemy = dynamic_cast<const Player*>(self);

	for (auto* fixture : m_hitFixtures) {
		b2Body* body = fixture->GetBody();
		auto* character = reinterpret_cast<Character*>(body->GetUserData().pointer);

		if (!character || !character->isVisible()) 
		{
			continue;
		}

		if (lookingForEnemy) {
			auto* enemy = dynamic_cast<Enemy*>(character);
			if (!enemy || enemy->isSpy()) continue; // Skip spies
		}
		else if (!dynamic_cast<Player*>(character)) continue;

		sf::Vector2f charPos = character->getPosition();
		float dx = charPos.x - lightPos.x;
		float dy = charPos.y - lightPos.y;
		float distSq = std::sqrt(dx * dx + dy * dy);

		if (distSq < minDistSq) {
			minDistSq = distSq;
			closestCharacter = character;
		}
	}

	//m_hitFixtures.clear();
	return closestCharacter;
}

void Character::updateTargets()
{

	m_hitFixtures.clear();
	if (!m_visionLight)
	{
		return;
	}

	float startAngle = m_visionLight->getRotation() - m_visionLight->getBeamAngle() / 2.f;
	float endAngle = m_visionLight->getRotation() + m_visionLight->getBeamAngle() / 2.f;

	const int rayCount = 100;
	float angleStep = (endAngle - startAngle) / static_cast<float>(rayCount);

	sf::Vector2f lightPos = m_visionLight->getPosition();
	b2Vec2 origin(lightPos.x / 30.f, lightPos.y / 30.f);  // تحويل للمتر

	for (int i = 0; i <= rayCount; ++i) {
		float angleDeg = startAngle + i * angleStep;
		float angleRad = angleDeg * b2_pi / 180.f;
		b2Vec2 direction(std::cos(angleRad), std::sin(angleRad));
		b2Vec2 endPoint = origin + (m_visionLight->getRange() / 30.f) * direction;

		RayCastClosest callback;
		m_world.getWorld().RayCast(&callback, origin, endPoint);

		if (callback.hit() && callback.getFixture()) {
			b2Body* body = callback.getFixture()->GetBody();
			if (body->GetType() == b2_dynamicBody && body != m_body) {
				m_hitFixtures.insert(callback.getFixture());
			}
		}
	}
	/*if (typeid(*this).name() == typeid(Player).name())
		std::cout << m_hitFixtures.size() << " targets" << std::endl;*/
}