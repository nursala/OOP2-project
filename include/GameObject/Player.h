#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include <Weapon.h>
class Player : public Entity {
public:
    Player(b2World& world);
    void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
    void setMoveStrategy(std::unique_ptr<MoveStrategy> strategy);
    void setLight(std::shared_ptr<VisionLight>& visionLight);
    void setWeaponLight(std::shared_ptr<WeaponLight>& weaponLight);
private:

    std::unique_ptr<MoveStrategy> m_moveStrategy;
	sf::RectangleShape m_shape; // For rendering the player
    std::unique_ptr<Weapon> m_weapon;
    std::shared_ptr<VisionLight> m_visionLight;


};
