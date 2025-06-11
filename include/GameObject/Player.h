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
	VisionLight& getVisionLight() {
		return m_weapon->getVisionLight();
	}
private:

    std::unique_ptr<MoveStrategy> m_moveStrategy;
	sf::RectangleShape m_shape; // For rendering the player
    std::unique_ptr<Weapon> m_weapon;

};
