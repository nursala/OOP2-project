#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "AnimationInc/Animation.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "MoveStrategyAndInfoInc/MoveInfo.h"
class Entity {
public:
    Entity(b2World& world, const sf::Texture* texture, sf::Vector2f position,
        sf::Vector2u imageCount, float switchTime);

    virtual void update(float deltaTime) = 0;  
    virtual void render(sf::RenderWindow& window);
    b2Vec2 getPositionB2() const;
    sf::Vector2f getPixels() const;
    void setPostion(const b2Vec2& position);
    virtual ~Entity() = default;
	void setVelocity(const b2Vec2& velocity);
	b2Vec2 getVelocity() const;
    b2Body* getBody() const;
	Animation& getAnimation();
    void setMoveStrategy(std::unique_ptr<MoveStrategy> strategy);
    const MoveInfo& getLastMoveInfo() const;
    const sf::Vector2f getDirection() const;
    bool isVisible() const { return m_visable; }
    void setVisible(bool visible) { m_visable = visible; }

protected:
    b2Body* m_body;
    sf::Sprite m_sprite;
    Animation m_animation;
	b2Vec2 m_velocity; 
    std::unique_ptr<MoveStrategy> m_moveStrategy;
	sf::RectangleShape m_hitbox; // For collision detection
	MoveInfo m_lastMoveInfo; // Last move info for the entity
	sf::Vector2f m_direction{ 0.f, 0.f }; // Current direction of the entity
    bool m_visable;

    static constexpr float SCALE = 30.f;
};
