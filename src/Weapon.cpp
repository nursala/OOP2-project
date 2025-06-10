#include "Weapon.h"

Weapon::Weapon(b2World& world, const sf::Vector2f& origin)
    : m_world(world),
	m_visionLight(100, 30) // Initialize VisionLight with range and beam angle
{
	m_shape.setSize(sf::Vector2f(100.f, 50.f));
	m_shape.setOrigin(m_shape.getSize() / 2.f);
	m_shape.setPosition(origin);
	m_shape.setFillColor(sf::Color::Green);
	m_visionLight.setColor(sf::Color::Red);
	m_visionLight.setIntensity(1.f); // Set the intensity of the vision light
}

void Weapon::fire(const sf::Vector2f& position, const sf::Vector2f& direction) {
    b2BodyDef bulletDef;
    bulletDef.type = b2_dynamicBody;
    bulletDef.position.Set(position.x / 30.f, position.y / 30.f);

    b2Body* bullet = m_world.CreateBody(&bulletDef);

    b2CircleShape shape;
    shape.m_radius = 5.f / 30.f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.2f;

    bullet->CreateFixture(&fixtureDef);

    // Apply velocity
    bullet->SetLinearVelocity(b2Vec2(direction.x * 10.f, direction.y * 10.f));
    m_bullets.push_back(bullet);
}

void Weapon::update(float dt  , sf::Vector2f playerPos) {
	m_shape.setPosition(playerPos);
	m_visionLight.update(playerPos, 0.f); // Assuming no rotation for simplicity
	// Update the vision light based on the bullets
	candle::EdgeVector edges;
	m_visionLight.castLight(edges.begin(), edges.end()); // Cast light using the edges
	
}

void Weapon::draw(sf::RenderWindow& window) {

    //window.draw(m_shape);
    window.draw(m_visionLight);

}
