#include "GameObject/Entity.h"
//Entity.cpp
Entity::Entity(b2World& world, const sf::Texture* texture, sf::Vector2f position,
	sf::Vector2u imageCount, float switchTime)
	: m_animation(texture, imageCount, switchTime)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE);
	m_body = world.CreateBody(&bodyDef);

	// شكل الجسم (دائرة)
	b2CircleShape shape;
	shape.m_radius = 10.f / SCALE;

	// إعداد الخصائص الفيزيائية
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.0f;

	// إنشاء الفيكستشر وتخزين المؤشر عليه
	b2Fixture* fixture = m_body->CreateFixture(&fixtureDef);
	fixture->GetUserData().pointer = reinterpret_cast<uintptr_t>(this); // ✅ وضع المؤشر على الكائن نفسه

	// (اختياري) وضع المؤشر على الجسم نفسه
	m_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

	m_body->CreateFixture(&fixtureDef);
	m_sprite.setPosition(position);
	m_sprite.setTexture(*texture);
	m_sprite.setTextureRect(m_animation.getUvRect());

	m_hitbox.setSize(sf::Vector2f(20.f, 20.f));
	m_visable = false;
}

void Entity::render(sf::RenderWindow& window) {
	if (m_visable)
		window.draw(m_hitbox);
}

void Entity::setPostion(const b2Vec2& position)
{
	if (m_body) {
		m_body->SetTransform(position, m_body->GetAngle());
	}
}

b2Vec2 Entity::getPositionB2() const {
	if (!m_body) {
		return b2Vec2(0, 0);
	}
	return { m_body->GetPosition().x ,m_body->GetPosition().y };
}

sf::Vector2f  Entity::getPixels() const {
	return { getPosition().x * SCALE, getPosition().y * SCALE };
}
void Entity::setVelocity(const b2Vec2& velocity) {
	if (m_body) {
		m_body->SetLinearVelocity(velocity);
	}
}

b2Vec2 Entity::getVelocity() const {
	return m_body ? m_body->GetLinearVelocity() : b2Vec2(0, 0);
}

b2Body* Entity::getBody() const
{
	return m_body;
}

Animation& Entity::getAnimation()
{
	return m_animation;
}

void Entity::setMoveStrategy(std::unique_ptr<MoveStrategy> strategy)
{
	m_moveStrategy = std::move(strategy);
}

const MoveInfo& Entity::getLastMoveInfo() const
{
	return m_lastMoveInfo;
}

const sf::Vector2f Entity::getPosition() const
{
	return m_hitbox.getPosition();
}


const sf::Vector2f Entity::getDirection() const
{
	return m_direction;
}