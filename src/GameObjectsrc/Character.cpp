#include "GameObject/Character.h"

Character::Character(World& world, const sf::Texture* texture, sf::Vector2f position,
    sf::Vector2u imageCount, float switchTime)
    : Entity(world, texture, position, imageCount, switchTime),
    m_world(world),
    m_healthBar(100.f, 10.f)
{

}

void Character::update(float deltaTime) {
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
        m_weapon->update(getPosition(),this->getBody()->GetAngle());
    }
    if (m_visionLight)
    {
        m_visionLight->update(getPosition(), this->getBody()->GetAngle());
    }

    m_sprite.setPosition(getPosition());
    m_sprite.setTextureRect(m_animation.getUvRect());

    sf::Vector2f healthBarPos = { getPosition().x , getPosition().y - 15 };
    m_healthBar.setPosition(healthBarPos);
}

void Character::render(sf::RenderWindow& window) {
    window.draw(m_sprite);
    /*  m_healthBar.draw(window)*/;
}

const MoveInfo& Character::getLastMoveInfo()
{
    return m_lastMoveInfo;
}

void Character::move(float dt)
{
    if (m_moveStrategy)
    {
        m_lastMoveInfo = m_moveStrategy->move(*this, dt);
    }
}

void Character::shoot(float dt) {
    //m_body->SetLinearVelocity(b2Vec2_zero);

  //  if (m_weapon) {
  //      auto bullet = m_weapon->fire(m_world, getPosition(), { 1,1 });
        //if (bullet) {
        //	m_world.addBullet(std::move(bullet));
        //}
  //  }
}

Weapon* Character::getWeapon() const
{
    return m_weapon.get();
}
