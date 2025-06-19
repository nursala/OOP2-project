// Character.h

#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "AttackingStrategyInc/AttakStrategy.h"
#include "StatesInc/State.h"
#include "WeponInc/Weapon.h"
#include "VisionLight.h"
#include "HealthBar.h"

class World;

class Character : public Entity 
{
public:
    Character(World& world, const sf::Texture* texture, sf::Vector2f position,
        sf::Vector2u imageCount, float switchTime);

    virtual ~Character() = default;

    void update(float deltaTime);
    void render(sf::RenderWindow& window) override;
    const MoveInfo& getLastMoveInfo();

    void move(float dt);

    void shoot(float dt);

    Weapon* getWeapon() const;

protected:
    World& m_world;

    std::unique_ptr<State> m_state;
    std::unique_ptr<AttackStrategy> m_attackStrategy;
    std::unique_ptr<MoveStrategy> m_moveStrategy;
    std::unique_ptr<Weapon> m_weapon;
    std::shared_ptr<VisionLight> m_visionLight;
    MoveInfo m_lastMoveInfo;
    HealthBar m_healthBar;
};


