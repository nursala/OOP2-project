#include "GameObject/ContactListener.h"
#include "GameObject/Entity.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "GameObject/Gift.h"
#include "GameObject/Bullet.h"
#include "WorldInc/World.h"
#include "ResourseInc/SoundManger.h"
#include <iostream>

ContactListener::ContactListener(World& world)
	: m_world(world) {
}

void ContactListener::BeginContact(b2Contact* contact) {
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	Entity* entityA = reinterpret_cast<Entity*>(bodyA->GetUserData().pointer);
	Entity* entityB = reinterpret_cast<Entity*>(bodyB->GetUserData().pointer);


	//if (!entityA || !entityB )
	//	return;

	// === Player Collisions ===
	if (auto player = dynamic_cast<Player*>(entityA)) {

		if (auto gift = dynamic_cast<Gift*>(entityB)) {
			switch (gift->getType()) {
			case Constants::GiftType::ARMOR:
				player->addArmor();
				SoundManger::instance().play(Constants::SoundID::SHIELDUPGRADE);
				break;
			case Constants::GiftType::HEALTH:
				player->addHealth();
				SoundManger::instance().play(Constants::SoundID::HEALTHUPGRADE);
				break;
			case Constants::GiftType::SPEEDUP:
				player->addSpeed();
				SoundManger::instance().play(Constants::SoundID::SPEEDUPGRADE);
				break;
			case Constants::GiftType::ENEMYSPEEDDOWN:
				for (auto enemy : m_world.getEnemies())
				{
					enemy->speedDown();
					SoundManger::instance().play(Constants::SoundID::SPEEDDOWN);
					enemy->setSpeedDownTimer(15.f);  // seconds of speed down
				}
				break;
			case Constants::GiftType::SPY:
				// Convert first non-spy enemy to spy
				for (auto enemy : m_world.getEnemies()) {
					if (!enemy->isSpy()) {
						enemy->setSpy(true);
						enemy->setSpyTimer(20.f);  //seconds of spy behavior
						break;
					}
				}
				break;
			case Constants::GiftType::VISIONUP:
				player->increaseVisionTemporarily(100.f, 10.f); // example: +100 radius for 10 seconds
				SoundManger::instance().play(Constants::SoundID::VISIONUPGRADE);
				break;
			default:
				throw std::runtime_error("Unknown Constants::GiftType");
			}
			gift->setDestroyed(true);
		}
	}

	// === bullet Collisions ===
	if (auto bullet = dynamic_cast<Bullet*>(entityA)) {
		if (auto character = dynamic_cast<Character*>(entityB)) {


			if (character == bullet->getOwnerShared().get())
			{
				return;
			}
			character->takeDamage(bullet->getDamage());
			bullet->setDestroyed(true);
		}
		else
		{
			bullet->setDestroyed(true);
		}
	}

	if (auto bullet = dynamic_cast<Bullet*>(entityB)) {
		if (auto character = dynamic_cast<Character*>(entityA)) {


			if (character == bullet->getOwnerShared().get())
			{
				return;
			}
			character->takeDamage(bullet->getDamage());
			bullet->setDestroyed(true);
		}
		else
		{
			bullet->setDestroyed(true);
		}
	}
	
}
