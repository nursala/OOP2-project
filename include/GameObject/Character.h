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

template<typename T>
class Character : public Entity {
public:
    Character(World& world, const sf::Texture* texture, sf::Vector2f position,
        sf::Vector2u imageCount, float switchTime);

    virtual ~Character() = default;

    void update(float deltaTime);
    void render(sf::RenderWindow& window) override;
    const MoveInfo& getLastMoveInfo();

protected:
    World& m_world;
    std::unique_ptr<State<T>> m_state;
    std::unique_ptr<AttackStrategy> m_attackStrategy;
    std::unique_ptr<MoveStrategy> m_moveStrategy;
    std::unique_ptr<Weapon> m_weapon;
    std::shared_ptr<VisionLight> m_visionLight;
    MoveInfo m_lastMoveInfo;
    HealthBar m_healthBar;

};

template<typename T>
Character<T>::Character(World& world, const sf::Texture* texture, sf::Vector2f position,
    sf::Vector2u imageCount, float switchTime)
    : Entity(world, texture, position, imageCount, switchTime),
    m_world(world),
    m_healthBar(50.f, 5.f,100,50)
{

}

template<typename T>
void Character<T>::update(float deltaTime) {
    if (m_state) {
        auto newState = m_state->handleInput(static_cast<T&>(*this));
        if (newState) {
            m_state = std::move(newState);
            m_state->enter(static_cast<T&>(*this));
        }
        m_state->update(static_cast<T&>(*this), deltaTime);
    }

    if (m_weapon)
    {
        m_weapon->update(getPosition(), m_sprite.getRotation());
    }
    if (m_moveStrategy)
        m_lastMoveInfo = m_moveStrategy->move(*this, deltaTime);
    m_sprite.setPosition(getPosition());
    m_sprite.setTextureRect(m_animation.getUvRect());

    sf::Vector2f healthBarPos = { getPosition().x , getPosition().y - 20 };
    m_healthBar.setPosition(healthBarPos);
}

template<typename T>
void Character<T>::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
    m_healthBar.draw(window);
  /*  if (m_weapon)
        m_weapon->draw(window);*/
}

template<typename T>
const MoveInfo& Character<T>::getLastMoveInfo()
{
    return m_lastMoveInfo;
}
