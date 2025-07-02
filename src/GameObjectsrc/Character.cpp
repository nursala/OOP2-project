#include "GameObject/Character.h"
#include "WorldInc/World.h"
#include "VisionLight.h"
#include <iostream>
#include "WeaponInc/Weapon.h"
#include "WeaponInc/HandGun.h"
#include "WeaponInc/Shotgun.h"
#include "WeaponInc/Sniper.h"
#include "ResourseInc/SoundManger.h"
#include "StatesInc/WalkingState.h"
#include "StatesInc/AttackingState.h"
#include "ResourseInc/TextureManager.h"


Character::Character(World& world, b2Vec2& positionB2)
	: Entity(world, positionB2)
{
	m_visionLight = std::make_unique<VisionLight>(300.f, 60.f); // Default range and beam angle
	m_visionLight->setIntensity(0.1f); // Set default intensity for the weapon light
	m_healthBar = std::make_unique<HealthBar>(50.f, 5.f, 100);
	m_visionLight->setScale(1.2f, 1.2f);
}

void Character::update(float deltaTime) 
{
	this->updateTargets();
	getClosestTarget();

	if (m_state) {
		auto newState = m_state->handleInput(*this);

		if (newState && m_state.get() != newState.get()) {
			m_state = std::move(newState);
			if (auto attackingState = dynamic_cast<WalkingState*>(m_state.get()))
			{
				auto& weaponData = Constants::WeaponDataMap.at(m_weapon->getType());

				m_animation->setAll(
					TextureManager::instance().get(weaponData.moveAnim.textureID),
					weaponData.moveAnim.frameSize,
					weaponData.moveAnim.speed
				);
				m_sprite.setTexture(*TextureManager::instance().get(weaponData.moveAnim.textureID));
			}
		}
		m_state->update(*this, deltaTime);
	}

	if (m_weapon)
	{
		m_weapon->update(getPosition(), this->getBody()->GetAngle(), deltaTime);
	}

	m_sprite.setPosition(getPosition());
	m_sprite.setTextureRect(m_animation->getUvRect());

	sf::Vector2f healthBarPos = { getPosition().x , getPosition().y + 30 };
	m_healthBar->setPosition(healthBarPos);
	m_healthBar->setValue(m_health);


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
	m_animation->update(deltaTime);
}

void Character::render(RenderLayers& renderLayers) {
	if (m_visable)
	{
		renderLayers.drawForeground(m_sprite);
		m_healthBar->draw(renderLayers);

		if (m_visionLight)
		{
			renderLayers.drawLight(*m_visionLight);
			renderLayers.drawForeground(*m_visionLight);
		}
		if (m_weapon)
			m_weapon->draw(renderLayers);
	}
	else
	{
		renderLayers.drawBackground(m_sprite);
	}
}

b2BodyType Character::getBodyType() const
{
	return b2_dynamicBody;
}

void Character::move(float dt)
{
	if (m_moveStrategy)
	{
		m_moveStrategy->move(*this, dt);
	}
}

Weapon* Character::getWeapon()
{
	return m_weapon.get();
}

void Character::shoot(float dt) {

	if (m_attackStrategy && m_weapon->getFireTimer() <= 0.f)
	{
		if (!m_attackStrategy->attack(*this, dt)) return;
		SoundManger::instance().play(Constants::WeaponDataMap.at(m_weapon->getType()).shootSound);
		auto& weaponData = Constants::WeaponDataMap.at(m_weapon->getType());

			m_animation->setAll(
			TextureManager::instance().get(weaponData.shootAnim.textureID),
			weaponData.shootAnim.frameSize,
			weaponData.shootAnim.speed
		);
		m_sprite.setTexture(*TextureManager::instance().get(weaponData.shootAnim.textureID));
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

void Character::updateTargets()
{
	m_hitFixtures.clear();
	if (!m_visionLight)
	{
		return;
	}

	float startAngle = m_visionLight->getRotation() - m_visionLight->getBeamAngle() / 2.f;
	float endAngle = m_visionLight->getRotation() + m_visionLight->getBeamAngle() / 2.f;

	const int rayCount = 36;
	float angleStep = (endAngle - startAngle) / static_cast<float>(rayCount);

	sf::Vector2f lightPos = m_visionLight->getPosition();
	b2Vec2 origin(lightPos.x / 30.f, lightPos.y / 30.f);

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

}