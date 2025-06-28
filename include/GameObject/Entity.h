#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "AnimationInc/Animation.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "MoveStrategyAndInfoInc/MoveInfo.h"
#include "Constants.h"

class World;
class RenderLayers; // Forward declaration
class Entity {
public:
	Entity(World& world, const sf::Texture* texture, sf::Vector2f position,
		sf::Vector2u imageCount, float switchTime);
	virtual ~Entity();

	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window);
	virtual void render(RenderLayers& renderLayers);
	b2Vec2 getPositionB2() const;

	sf::Vector2f getPosition() const;
	void setPosition(const b2Vec2& position);
	void setVelocity(const b2Vec2& velocity);
	b2Vec2 getVelocity() const;
	b2Body* getBody() const;
	Animation& getAnimation();
	void adjustSpriteToFixtureSize();
	World& getWorld();
	bool isVisible() const { return m_visable; }
	void setVisible(bool visible) { m_visable = visible; }
	void setDestroyed(bool destroyed) { m_destroyed = destroyed; }
	bool isDestroyed() const { return m_destroyed; }
	void setSpriteRadius(float radius);
	sf::Vector2f getSpriteRadius() const {
		return m_sprite.getScale();
	}
	void init(b2BodyType type, float radius);


protected:
	bool m_visable;
	bool m_destroyed = false;

	b2Body* m_body = nullptr;
    World& m_world;
	float m_bodyRadius = 0.f; // Used for circle bodies

	sf::Sprite m_sprite;
	Animation m_animation;
	sf::Vector2f m_position;
	sf::Vector2f m_initialPosition;
	
	virtual void customizeBodyDef(b2BodyDef&) {}
	virtual void customizeFixtureDef(b2FixtureDef&) {}
	virtual b2BodyType getBodyType() const { return b2_dynamicBody; }
	static constexpr float SCALE = 30.f;
};
