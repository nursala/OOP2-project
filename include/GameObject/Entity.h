#pragma once

//========================= Includes =========================//
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include <unordered_map>
#include "AnimationInc/Animation.h"
#include "MoveStrategyAndInfoInc/MoveStrategy.h"
#include "Constants.h"

//========================= Forward Declarations =========================//
class World;
class RenderLayers;
class Player;
class Enemy;
class Gift;
class Bullet;

//========================= Class Entity =========================//
class Entity {
public:
    //========================= Constructor / Destructor =========================//
    Entity(World& world, const b2Vec2& positionB2);
    virtual ~Entity();

    //========================= Public Virtual Methods =========================//
    virtual void update(float deltaTime) = 0;
    virtual void render(RenderLayers& renderLayers);

    //========================= Collision Methods (Double Dispatch) =========================//
    virtual Constants::EntityType getEntityType() const = 0;

    virtual void onCollide(Entity& other) = 0;
    virtual void onCollideWith(Player& player) {}
    virtual void onCollideWith(Enemy& enemy) {}
    virtual void onCollideWith(Gift& gift) {}
    virtual void onCollideWith(Bullet& bullet) {}

    //========================= Public Utility Methods =========================//
    void init(const b2BodyType type, const float radius);
    sf::Vector2f getPosition() const;
    b2Vec2 getPositionB2() const;
    void setPosition(const b2Vec2& position);
    void setVelocity(const b2Vec2& velocity);
    b2Vec2 getVelocity() const;
    b2Body* getBody() const;
    World& getWorld();

    void setSpriteRadius(const float radius);
    sf::Vector2f getSpriteRadius() const { return m_sprite.getScale(); }

    bool isVisible() const { return m_visable; }
    void setVisible(const bool visible) { m_visable = visible; }

    void setDestroyed(const bool destroyed) { m_destroyed = destroyed; }
    bool isDestroyed() const { return m_destroyed; }

protected:
    bool m_visable = true;
    bool m_destroyed = false;

    b2Body* m_body = nullptr;
    World& m_world;

    float m_bodyRadius = 0.f;

    sf::Sprite m_sprite;
    b2Vec2 m_position;
    b2Vec2 m_initialPosition;

    float SCALE = 30.f;

    Constants::EntityType m_entityType;

    virtual void customizeBodyDef(b2BodyDef&) {}
    virtual void customizeFixtureDef(b2FixtureDef&) {}
    virtual b2BodyType getBodyType() const { return m_body->GetType(); }

private:
    void adjustSpriteToFixtureSize();
};
