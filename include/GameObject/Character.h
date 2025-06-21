// Character.h

#pragma once

#include "GameObject/Entity.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "AttackingStrategyInc/AttakStrategy.h"
#include "StatesInc/State.h"
#include "HealthBar.h"

class Weapon;
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
    virtual b2BodyType getBodyType() const override;
    void move(float dt);

    virtual void shoot(float dt) = 0;

    Weapon* getWeapon();
    virtual sf::Vector2f getTarget() const = 0;

protected:

    std::unique_ptr<State> m_state;
    std::unique_ptr<AttackStrategy> m_attackStrategy;
    std::unique_ptr<MoveStrategy> m_moveStrategy;
    std::unique_ptr<Weapon> m_weapon;
    MoveInfo m_lastMoveInfo;
    HealthBar m_healthBar;
};