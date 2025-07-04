//========================= Includes =========================//
#include "GameObject/Entity.h"
#include "WorldInc/World.h"
#include <iostream>

//========================= Constructor =========================//
Entity::Entity(World& world, const b2Vec2& positionB2)
    : m_world(world), m_position(positionB2), m_visable(true)
{
    m_initialPosition = m_position;
    setPosition(positionB2);
    m_sprite.setPosition(sf::Vector2f(positionB2.x, positionB2.y));
}

//========================= Destructor =========================//
Entity::~Entity() {
    if (m_body) {
        m_body->GetWorld()->DestroyBody(m_body);
        m_body = nullptr;
    }
}

//========================= Initialization =========================//
void Entity::init(b2BodyType type, float radius)
{
    // Define the body
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position.Set(m_position.x / SCALE, m_position.y / SCALE);
    bodyDef.gravityScale = 0.f;

    customizeBodyDef(bodyDef);  // Allow subclasses to customize
    m_body = m_world.getWorld().CreateBody(&bodyDef);

    // Create a circular shape fixture
    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    customizeFixtureDef(fixtureDef);  // Allow subclasses to customize

    b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);
    fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
    m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    adjustSpriteToFixtureSize();
}

//========================= Rendering =========================//
void Entity::render(RenderLayers& renderLayers) {
    if (m_visable)
        renderLayers.drawForeground(m_sprite);
    else
        renderLayers.drawBackground(m_sprite);
}

//========================= Position and Movement =========================//
void Entity::setPosition(const b2Vec2& position)
{
    if (m_body) {
        m_body->SetTransform({ position.x / SCALE, position.y / SCALE }, m_body->GetAngle());
        m_sprite.setPosition(position.x, position.y);
    }
}

b2Vec2 Entity::getPositionB2() const {
    return m_body ? m_body->GetPosition() : b2Vec2(0, 0);
}

sf::Vector2f Entity::getPosition() const {
    b2Vec2 pos = getPositionB2();
    return { pos.x * SCALE, pos.y * SCALE };
}

void Entity::setVelocity(const b2Vec2& velocity) {
    if (m_body)
        m_body->SetLinearVelocity(velocity);
}

b2Vec2 Entity::getVelocity() const {
    return m_body ? m_body->GetLinearVelocity() : b2Vec2(0, 0);
}

b2Body* Entity::getBody() const {
    return m_body;
}

//========================= Sprite Handling =========================//
void Entity::adjustSpriteToFixtureSize()
{
    if (!m_body || !m_body->GetFixtureList())
        return;

    b2Fixture* fixture = m_body->GetFixtureList();
    sf::Vector2f desiredSize;

    // Only supports circular shapes
    if (fixture->GetShape()->GetType() == b2Shape::e_circle) {
        float radius = static_cast<b2CircleShape*>(fixture->GetShape())->m_radius;
        float diameter = radius * 2.f * SCALE;
        desiredSize = { diameter, diameter };
    }
    else {
        return;
    }

    sf::IntRect frameRect = m_sprite.getTextureRect();
    sf::Vector2f frameSize(static_cast<float>(frameRect.width), static_cast<float>(frameRect.height));

    constexpr float spriteRadiusFactor = 1.2f;

    sf::Vector2f scale = {
        (desiredSize.x * spriteRadiusFactor) / frameSize.x,
        (desiredSize.y * spriteRadiusFactor) / frameSize.y
    };

    m_sprite.setScale(scale);
    m_sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
}

void Entity::setSpriteRadius(float radius)
{
    m_sprite.setScale(m_sprite.getScale().x * radius, m_sprite.getScale().y * radius);
}

//========================= World Access =========================//
World& Entity::getWorld() {
    return m_world;
}
