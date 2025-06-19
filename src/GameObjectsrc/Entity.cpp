#include "GameObject/Entity.h"
#include "WorldInc/World.h"

#include <iostream>

Entity::Entity(World& world, const sf::Texture* texture, sf::Vector2f position, sf::Vector2u imageCount, float switchTime)

	: m_animation(texture, imageCount, switchTime)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
	bodyDef.gravityScale = 0.f;

	customizeBodyDef(bodyDef);

	m_body = world.getWorld().CreateBody(&bodyDef);


	b2CircleShape shape;
	shape.m_radius = 10.f / SCALE;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);
	fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

	m_sprite.setTexture(*texture);
	m_sprite.setTextureRect(m_animation.getUvRect());
	this->adjustSpriteToFixtureSize();
	m_sprite.setPosition(position);
	m_visable = false;
}



void Entity::render(sf::RenderWindow& window) {
	if (m_visable)
		window.draw(m_sprite);
}

void Entity::setPostion(const b2Vec2& position)
{
	if (m_body) {
		m_body->SetTransform({ position.x / SCALE, position.y / SCALE }, m_body->GetAngle());
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

Animation& Entity::getAnimation() {
	return m_animation;
}

float Entity::getSpeed() const {
	return m_speed;
}
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

	sf::Vector2f scale = {
		desiredSize.x / frameSize.x,
		desiredSize.y / frameSize.y
	};

	m_sprite.setScale(scale);
	m_sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f);
}
