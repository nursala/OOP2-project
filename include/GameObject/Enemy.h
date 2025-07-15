//=========================================================
// Description: Represents an enemy character in the game.
//              Inherits from Character and implements AI logic
//=========================================================

#pragma once

#include "GameObject/Character.h"
#include "GameObject/Player.h"
#include <SFML/Graphics.hpp>

class LoadMap;
class World;

class Enemy : public Character
{
public:
	//==========================
	// Constructor / Destructor
	//==========================
	Enemy(World& world, const b2Vec2& position, const LoadMap& map,
		const Player& player, const Constants::WeaponType& type);
	virtual ~Enemy() override = default;

	//==========================
	// Override Character methods
	//==========================
	void takeDamage(const int damage) override;
	void update(const float deltaTime) override;

	//==========================
	// Spy Mechanism
	//==========================
	bool isSpy() const;
	void setSpy(const bool value, const float seconds = 0);

	//==========================
	// Speed Control
	//==========================
	void speedDown();
	void setSpeedDownTimer(const float seconds);


	//==========================
	// Footstep Sound
	//==========================
	void updateFootstepSound(const float distanceToPlayer, const float deltaTime);
	//==========================
	// Collision Handling
	//==========================
	virtual Constants::EntityType getEntityType() const override { return m_entityType; }
	virtual void onCollide(Entity& other) override;
	virtual void onCollideWith(Bullet& bullet) override;

private:
	//==========================
	// References
	//==========================
	const Player& m_playerRef;

	//==========================
	// State Flags & Timers
	//==========================
	bool m_isSpy = false;
	float m_spyTimer = 0.f;
	float m_speedDownTimer = 0.f;
	float m_footstepTimer = 0.f;
	float m_footstepInterval = 1.f;
	float m_originalSpeed = 5.f;
	float m_hideDelayTimer = 0.f;

	//==========================
	// Override Character methods
	//==========================
	virtual void getClosestTarget() override;
	bool isValidTarget(Character* character) const;
};
