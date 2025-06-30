#include "GameObject/Entity.h"
#include "WorldInc/World.h"

#include <iostream>

Entity::Entity(World& world, b2Vec2& positionB2) : m_world(world), m_position(positionB2)
{
	//if (texture)
	//{
	//	m_sprite.setTexture(*texture);
	//	m_sprite.setTextureRect(m_animation.getUvRect());
	//}

	m_initialPosition = m_position;
	m_sprite.setPosition(getPosition());
	m_visable = true;
}

Entity::~Entity() {
	if (m_body) {
		m_body->GetWorld()->DestroyBody(m_body);
		m_body = nullptr;
	}
}

void Entity::init(b2BodyType type, float radius)
{
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(m_position.x / SCALE, m_position.y / SCALE);
	bodyDef.gravityScale = 0.f;

	customizeBodyDef(bodyDef); 

	m_body = m_world.getWorld().CreateBody(&bodyDef);

	b2CircleShape shape;
	shape.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 0.0f;
	customizeFixtureDef(fixtureDef);

	b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);
	fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

	this->adjustSpriteToFixtureSize(); // Adjust sprite size based on fixture size
}



void Entity::render(sf::RenderWindow& window) {
	if (m_visable)
		window.draw(m_sprite);
}

void Entity::render(RenderLayers& renderLayers) {
	if (m_visable)
		renderLayers.drawForeground(m_sprite);
	else
		renderLayers.drawBackground(m_sprite); 
}

void Entity::setPosition(const b2Vec2& position)
{
	m_position = {position.x, position.y};
	if (m_body) {
		m_body->SetTransform({ position.x / SCALE, position.y / SCALE }, m_body->GetAngle());
		m_sprite.setPosition(position.x, position.y);
	}
}

b2Vec2 Entity::getPositionB2() const {
	if (!m_body) {
		return b2Vec2(0, 0);
	}
	return m_body->GetPosition();
}

sf::Vector2f Entity::getPosition() const {
	if (!m_body) return { 0.f, 0.f };
	b2Vec2 pos = m_body->GetPosition();
	return { pos.x * SCALE, pos.y * SCALE };
}

void Entity::setVelocity(const b2Vec2& velocity) {
	if (m_body) {
		m_body->SetLinearVelocity(velocity);
	}
}

b2Vec2 Entity::getVelocity() const {
	return m_body ? m_body->GetLinearVelocity() : b2Vec2(0, 0);
}

b2Body* Entity::getBody() const {
	return m_body;
}

//Animation& Entity::getAnimation() {
//	return m_animation;
//}

void Entity::adjustSpriteToFixtureSize()
{
	if (!m_body || !m_body->GetFixtureList())
		return;

	b2Fixture* fixture = m_body->GetFixtureList();
	sf::Vector2f desiredSize;

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

	float spriteRadiusFactor = 1.2f;

	sf::Vector2f scale = {
		(desiredSize.x * spriteRadiusFactor) / frameSize.x,
		(desiredSize.y * spriteRadiusFactor) / frameSize.y
	};

	m_sprite.setScale(scale);
	m_sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
}

World& Entity::getWorld() {
	return m_world;
}

void Entity::setSpriteRadius(float radius)
{
	m_sprite.setScale(m_sprite.getScale().x * radius, m_sprite.getScale().y * radius);
	b2FixtureDef fixtureDef;
}
