#include "WeponInc/Weapon.h"

Weapon::Weapon(b2World& world):
    m_world(world)
{

}

void Weapon::fire(const sf::Vector2f& position, const sf::Vector2f& direction)
{
    //// هذه مجرد فكرة لإنشاء جسم Box2D كرصاصة (بدون رسمة حالياً)
    //b2BodyDef bulletDef;
    //bulletDef.type = b2_dynamicBody;
    //bulletDef.position.Set(position.x / 30.f, position.y / 30.f); // تحويل إلى وحدة Box2D

    //b2Body* bulletBody = m_world.CreateBody(&bulletDef);

    //b2CircleShape bulletShape;
    //bulletShape.m_radius = 5.f / 30.f; // 5 بكسل

    //b2FixtureDef fixtureDef;
    //fixtureDef.shape = &bulletShape;
    //fixtureDef.density = 1.f;
    //fixtureDef.friction = 0.f;
    //fixtureDef.restitution = 0.f;
    //fixtureDef.isSensor = true;

    //bulletBody->CreateFixture(&fixtureDef);

    //// تحديد السرعة
    //b2Vec2 velocity(direction.x, direction.y);
    //velocity.Normalize();
    //velocity *= 20.f;
    //bulletBody->SetLinearVelocity(velocity);

    //m_bullets.push_back(bulletBody);
}

void Weapon::update(sf::Vector2f playerPos, float angle)
{
    if (m_weaponLight)
    {
        m_weaponLight->setPosition(playerPos);
        m_weaponLight->update(playerPos, angle);
    }

}

void Weapon::draw(sf::RenderWindow& window)
{
    if (m_weaponLight)
        window.draw(*m_weaponLight);
}

void Weapon::setLight(std::shared_ptr<WeaponLight>& weaponLight)
{
    m_weaponLight = weaponLight;
}
