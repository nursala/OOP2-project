#include "GameObject/Bullet.h"
#include "GameObject/Player.h"
#include "GameObject/Enemy.h"
#include "WorldInc/World.h"
#include "ResourseInc/TextureManager.h"
#include "Factory.h"
#include <cmath>
#include <iostream>

namespace {
    // Register Bullet with the factory
    bool registered = [] {
        Factory::instance().registerType<Bullet,
            World&,
            const b2Vec2&,
            const sf::Vector2f&,
            const std::shared_ptr<Character>&,
            const float&,
            const float&>(Constants::EntityType::Bullet);
        return true;
        }();
}

//---------------------------------------------
// Constructor: Initializes texture, direction, damage, range, and body
//---------------------------------------------
Bullet::Bullet(World& world, const b2Vec2& positionB2, const sf::Vector2f& direction,
    const std::shared_ptr<Character>& owner, const float& damage, const float& range)
    : Entity(world, positionB2), m_direction(direction), m_owner(owner)
{
    m_entityType = Constants::EntityType::Bullet;

    m_sprite.setTexture(*TextureManager::instance().get(Constants::TextureID::BULLET));
    m_sprite.setTextureRect(sf::IntRect(0, 0,
        TextureManager::instance().get(Constants::TextureID::BULLET)->getSize().x,
        TextureManager::instance().get(Constants::TextureID::BULLET)->getSize().y));

    m_damage = damage;
    m_range = range + 10.f; // Small buffer
    init(b2_kinematicBody, 0.3f); // Radius of 0.3f
}

//---------------------------------------------
// Customize the body to act as a fast-moving bullet
//---------------------------------------------
void Bullet::customizeBodyDef(b2BodyDef& bodyDef)
{
    bodyDef.bullet = true;
}

//---------------------------------------------
// Set fixture as a sensor (non-colliding trigger)
//---------------------------------------------
void Bullet::customizeFixtureDef(b2FixtureDef& fixtureDef)
{
    fixtureDef.isSensor = true;
}

//---------------------------------------------
// Returns the Box2D body type (kinematic)
//---------------------------------------------
b2BodyType Bullet::getBodyType() const
{
    return b2_kinematicBody;
}

//---------------------------------------------
// Moves the bullet, updates position, destroys if range exceeded
//---------------------------------------------
void Bullet::update(float deltaTime)
{
    if (!m_body || m_destroyed) return;

    // Update velocity
    b2Vec2 velocity(m_direction.x * m_speed, m_direction.y * m_speed);
    m_body->SetLinearVelocity(velocity);

    // Update sprite position
    b2Vec2 pos = m_body->GetPosition();
    m_sprite.setPosition(pos.x * SCALE, pos.y * SCALE);
    m_position = { pos.x * SCALE, pos.y * SCALE };

    // Check distance travelled
    float dx = m_position.x - m_initialPosition.x;
    float dy = m_position.y - m_initialPosition.y;
    float distance = std::sqrt(dx * dx + dy * dy);
    if (distance > m_range)
        m_destroyed = true;
}

//---------------------------------------------
// Returns a shared_ptr to the bullet's owner
//---------------------------------------------
std::shared_ptr<Character> Bullet::getOwnerShared() const {
    return m_owner.lock();
}

//---------------------------------------------
// Returns bullet damage
//---------------------------------------------
float Bullet::getDamage() const
{
    return m_damage;
}

//==================================================
// Double Dispatch Handlers
//==================================================
void Bullet::onCollide(Entity& other)
{
    other.onCollideWith(*this);
}

void Bullet::onCollideWith(Player& player)
{
    auto shooter = getOwnerShared();
    if (!shooter || shooter.get() == &player) return;

    if (shooter->getEntityType() == Constants::EntityType::Enemy) {
        player.takeDamage(m_damage);
        setDestroyed(true);
    }
}

void Bullet::onCollideWith(Enemy& enemy)
{
    auto shooter = getOwnerShared();
    if (!shooter || shooter.get() == &enemy) return;

    bool isShooterPlayer = shooter->getEntityType() == Constants::EntityType::Player;
    bool isShooterSpy = shooter->getEntityType() == Constants::EntityType::Spy;

    if ((isShooterPlayer || isShooterSpy) && !enemy.isSpy()) {
        enemy.takeDamage(m_damage);
        setDestroyed(true);
        enemy.setTarget(shooter);
    }
}
