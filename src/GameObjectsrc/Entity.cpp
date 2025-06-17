#include "GameObject/Entity.h"
#include <iostream>

Entity::Entity(b2World& world, const sf::Texture* texture, sf::Vector2f position,
	sf::Vector2u imageCount, float switchTime)
	: m_animation(texture, imageCount, switchTime)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
	bodyDef.gravityScale = 0.f;
	m_body = world.CreateBody(&bodyDef);

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
	m_sprite.setTextureRect(m_animation.getUvRect()); // قبل الحساب!
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

sf::Vector2f Entity::getPixels() const {
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

void Entity::setMoveStrategy(std::unique_ptr<MoveStrategy> strategy) {
	m_moveStrategy = std::move(strategy);
}

const MoveInfo& Entity::getLastMoveInfo() const {
	return m_lastMoveInfo;
}

const sf::Vector2f Entity::getDirection() const {
	return m_direction;
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
		// حساب القطر (2 × نصف القطر) وتحويله إلى بكسل
		float radius = static_cast<b2CircleShape*>(fixture->GetShape())->m_radius;
		float diameter = radius * 2.f * SCALE;
		desiredSize = { diameter, diameter };
	}
	else if (fixture->GetShape()->GetType() == b2Shape::e_polygon) {
		auto poly = static_cast<b2PolygonShape*>(fixture->GetShape());
		b2Vec2 lower(FLT_MAX, FLT_MAX), upper(-FLT_MAX, -FLT_MAX);
		for (int i = 0; i < poly->m_count; ++i) {
			const auto& v = poly->m_vertices[i];
			lower = b2Min(lower, v);
			upper = b2Max(upper, v);
		}
		float width = (upper.x - lower.x) * SCALE;
		float height = (upper.y - lower.y) * SCALE;
		desiredSize = { width, height };
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
	m_sprite.setOrigin(frameSize.x / 2.f, frameSize.y / 2.f); // توسيط السبرايت
}
