#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "AnimationInc/Animation.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "MoveStrategyAndInfoInc/MoveInfo.h"

class World;
class Entity {
public:
	Entity(World& world, const sf::Texture* texture, sf::Vector2f position,
		sf::Vector2u imageCount, float switchTime);

	virtual void update(float deltaTime) = 0;
	virtual void render(sf::RenderWindow& window);

	b2Vec2 getPositionB2() const;

	sf::Vector2f getPosition() const;


	void setPostion(const b2Vec2& position);

	virtual ~Entity() = default;

	void setVelocity(const b2Vec2& velocity);
	b2Vec2 getVelocity() const;
	b2Body* getBody() const;

	Animation& getAnimation();

	float getSpeed() const;

	void adjustSpriteToFixtureSize();

	bool isVisible() const { return m_visable; }
	void setVisible(bool visible) { m_visable = visible; }

protected:
	b2Body* m_body = nullptr;

	sf::Sprite m_sprite;
	Animation m_animation;

	bool m_visable = false;
	float m_speed = 0.f;

	static constexpr float SCALE = 30.f;

};
