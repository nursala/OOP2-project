#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "StatesInc/State.h"
#include "GameObject/HealthBar.h"


#include <Weapon.h>
class Player : public Entity {
public:
    Player(b2World& world);
    void update(float deltaTime) override;
    void setFacingRight(bool isFaceRight);
	void render(sf::RenderWindow& window) override;
    void takeDamage(float amount);
    //void setMoveStrategy(std::unique_ptr<MoveStrategy> strategy);
    void setLight(std::shared_ptr<VisionLight>& visionLight);
    void setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight);
private:
	std::unique_ptr<State<Player>> m_state; // Current state of the player
	sf::RectangleShape m_shape; // For rendering the player
	MoveInfo m_lastMoveInfo; // Last move info for the player
    std::unique_ptr<Weapon> m_weapon;
    std::shared_ptr<VisionLight> m_visionLight;
    HealthBar m_healthBar;
    float m_health; // Player's current health
    float m_maxHealth; // Player's max health


};
